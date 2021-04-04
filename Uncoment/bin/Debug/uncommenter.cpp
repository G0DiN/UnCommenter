
  return res;
}

_variant_t fnSelCriterionGlass(int Row, int Col, _variant_t Val)
{
  long  id = Val.vt != VT_NULL ? long(Val) : 0;

  DlgCritSetForWMater  Dlg ("", id, e_idtype_idWriteMaterRule, NULL);
  Dlg.m_nMode = e_cmGlass;

  long  res = 0;
  if ( Dlg.DoModal() == IDOK )
    res = Dlg.m_Grid.GetGridModifyStatus()? 1 : 0;

  return res;
}

CRuleGrid::CRuleGrid (char* lpsz) : CADOGridRecord (lpsz)
{
  m_pDlgMater = NULL;
  m_pParent   = NULL;
}

bool CRuleGrid::OnBeforeAddNew(UINT nChar)
{
  CWaitCursor  wait;            if ( ShowMaterialDlg ((void**)&m_pDlgMater, &m_pParent->m_idMaterial, theApp.GetMainFrame()->m_Conn, this) )
    return true;
  return false;
}

void CRuleGrid::OnAddNew()
{
  if ( m_pParent->m_eWMType == e_Glass )
  {
    m_Recordset->Fields->GetItem("idMaterial"  )->Value = m_pParent->m_idMaterial;
    m_Recordset->Fields->GetItem("nWriteType"  )->Value = (long)e_WriteType_CountOnSeg;      m_Recordset->Fields->GetItem("idMaterGroup")->Value = 8L;       m_Recordset->Fields->GetItem("nCount"      )->Value = 1L;
  }
  else
  if ( m_pParent->m_eWMType == e_Profile )
  {
    m_Recordset->Fields->GetItem("idMaterial"  )->Value = m_pParent->m_idMaterial;
    m_Recordset->Fields->GetItem("nWriteType"  )->Value = (long)e_WriteType_MaxLengSeg;       m_Recordset->Fields->GetItem("idMaterGroup")->Value = 17L;      m_Recordset->Fields->GetItem("nCount"      )->Value = 1L;
    m_Recordset->Fields->GetItem("idProfile"   )->Value = m_pParent->m_idProfile;    }
  else
  if ( m_pParent->m_eWMType == e_ProfileDist )
  {
    m_Recordset->Fields->GetItem("idMaterial"   )->Value = m_pParent->m_idMaterial;
    m_Recordset->Fields->GetItem("nWriteType"   )->Value = (long)e_WriteType_CountOnDistance;       m_Recordset->Fields->GetItem("idMaterGroup" )->Value = 28L;      m_Recordset->Fields->GetItem("nCount"       )->Value = 1L;
    m_Recordset->Fields->GetItem("idProfileDist")->Value = m_pParent->m_idProfile;            }
  m_Recordset->Update();
}

void CRuleGrid::OnContextMenu(CWnd* pWnd, CPoint point)
{
  try
  {
    if ( !m_Recordset->GetRecordCount() )
      return;

    CRect  rect;
    GetWindowRect(rect);

    CPoint  NulPoint = rect.TopLeft(),
            ShiftPoint;

    ShiftPoint.x = point.x - NulPoint.x;
    ShiftPoint.y = point.y - NulPoint.y;

    CCellID  Cell = GetCellFromPt(ShiftPoint);

    if ( Cell.row == 0 )
      return;

    CGridCellBase *CurrCell = GetCell(Cell.row, Cell.col);

    if ( !CurrCell )
      return;

    if ( !CurrCell->IsSelected() )
    {
      OnLButtonDown(0, ShiftPoint);
      OnLButtonUp  (0, ShiftPoint);
      Select_Record(Cell.row);
    }

    Select_Cur();
    if ( point.x == -1  &&  point.y == -1 )
    {
      CRect rect;
      GetWindowRect(rect);

      point = rect.TopLeft() + CPoint(10, 10);
    }
    SetFocus();

    CMenu  menu;

    menu.LoadMenu(IDR_POPUP_WMR);

    if ( !aList.IsEmpty() )
      menu.EnableMenuItem(IDC_PASTE_PROF_WRITE, false);
    else
      menu.EnableMenuItem(IDC_PASTE_PROF_WRITE, true);

    menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, point.x, point.y, pWnd);
  }
  CATCH_SHOW(__FILE__, __LINE__, __FUNCTION__)
}

void CRuleGrid::OnLButtonUp(UINT nFlags, CPoint point)
{
  try
  {
    CCellID clickCell = GetCellFromPt(point);
    if ( clickCell.row == 0 )
    {
      CADOGridRecord::OnLButtonUp(nFlags, point);
      return;
    }

        CCellID  CurCell = m_idCurrentCell;
    long
      nRow    = CurCell.row,
      nCol    = CurCell.col;

    CADOGridLinkFieldMaster  *pF = (CADOGridLinkFieldMaster*)GetFieldMaster(GetFieldNum(CurCell.col));

    if ( pF && (pF->FieldName == "NumberScript" || pF->FieldName == "ConditionScript") )
    {
      CADOGridRecord::OnLButtonUp(nFlags, point);
      return;
    }

    if ( pF && pF->GetIsButton() )
    {
      if ( Select_Cur() )
      {
        _bstr_t         FN           = pF->FieldName;
        CGridBtnCell  * pGridBtnCell = (CGridBtnCell*)GetCell(nRow, nCol);

        if ( pGridBtnCell->GetLastCtlClicked() == 0 )
        {
          UpdateBatch();
          Init_Cur();

          SetFocusCell(CurCell);
          Select_Cur();

          CGridCtrl::OnLButtonUp(nFlags, point);

          long  ID  = ConvertLong(m_Recordset, "ID"),
                res = pF->BnClick(nRow, nCol, _variant_t(ID));

          if ( res )            {
            RequeryAll();
            Init();

            if ( GetViewColNum("CriterionExist") != -1 )
              AutoSizeColumn(GetViewColNum("CriterionExist"));

            EnableTitleTips(false);
            Invalidate(true);
          }
        }
      }
    }
  }
  CATCH_SHOW(__FILE__, __LINE__, __FUNCTION__)
  CADOGridRecord::OnLButtonUp(nFlags, point);
}

void CRuleGrid::OnCopyProfWriteWM()
{
  try
  {
    GetSelIdArray("ID", aList);
    if ( aList.IsEmpty() )
    {
      ABMessageBox("Р СњР Вµ Р Р†РЎвЂ№Р Т‘Р ВµР В»Р ВµР Р…Р С• Р Р…Р С‘ Р С•Р Т‘Р Р…Р С•Р в„– РЎРѓРЎвЂљРЎР‚Р С•Р С”Р С‘!");
      return;
    }
  }
  CATCH_SHOW(__FILE__, __LINE__, __FUNCTION__)
}

void CRuleGrid::OnPasteProfWriteWM()
{
  try
  {
    CWaitCursor  wc;
    CString      sSQL;
    int          iCount = (int)aList.GetCount();

    if ( GetGridModifyStatus() )
      UpdateBatch();  
    for (int i = 0; i < iCount; i++)
    {
      long  ID = aList[i];
      sSQL.Format("exec sp_CopyMaterWrite %li, %li, 'idProfile'", m_pParent->m_idProfile, ID);
      RunSQL(sSQL, theApp.GetMainFrame()->m_Conn);
    }

    m_Recordset->Requery(adOptionUnspecified);

        Init();

                  }
  CATCH_SHOW(__FILE__, __LINE__, __FUNCTION__)
}

void CRuleGrid::OnProtocolDel()
{
  try
  {
    DlgProtocol  Dlg(0, 19);
    Dlg.DoModal();
  }
  CATCH_HIDE(__FILE__, __LINE__, __FUNCTION__)
}

void CRuleGrid::ChangeMaterial()
{
  CWaitCursor  wait;          
  if ( Select_Cur() )
    if ( ShowMaterialDlg ((void**)&m_pDlgMater, &m_pParent->m_idMaterial, theApp.GetMainFrame()->m_Conn, this) )
    {
      m_Recordset->Fields->GetItem("idMaterial")->Value = m_pParent->m_idMaterial;
      m_Recordset->Update();
      Init_Cells();
    }
}


IMPLEMENT_DYNAMIC(DlgWriteMaterRule, DlgAbstract)
BEGIN_MESSAGE_MAP(DlgWriteMaterRule, DlgAbstract)
  ON_BN_CLICKED(IDOK,            OnBnClickedOk    )
  ON_BN_CLICKED(IDCANCEL,        OnBnClickedCancel)
  ON_BN_CLICKED(IDC_WMR_SHTAPIK, OnBnWMRShtapik   )
END_MESSAGE_MAP()

DlgWriteMaterRule::DlgWriteMaterRule(eWriteMaterialType eWMType, long idProfile, LPCTSTR szGridProfile, CWnd* pParent   : DlgAbstract(DlgWriteMaterRule::IDD, pParent),
    m_Grid (szGridProfile? ("DlgWriteMaterRule\\Grid\\" + (CString)szGridProfile).GetBuffer() : "DlgWriteMaterRule\\Grid\\")
{
  m_Grid.m_pParent = this;
  m_idMaterial     = 0;
  m_eWMType        = eWMType;
  m_idProfile      = idProfile;
}

DlgWriteMaterRule::~DlgWriteMaterRule()
{
}

void DlgWriteMaterRule::DoDataExchange(CDataExchange* pDX)
{
  DlgAbstract::DoDataExchange(pDX);
  DDX_Control(pDX, IDOK,            m_btnOk        );
  DDX_Control(pDX, IDCANCEL,        m_btnCancel    );
  DDX_Control(pDX, IDC_GRID,        m_Grid         );
  DDX_Control(pDX, IDC_WMR_SHTAPIK, m_btnWMRShtapik);
}

BOOL DlgWriteMaterRule::OnInitDialog()
{
  TRACE("%s(%i) : %s\r\n", __FILE__, __LINE__, __FUNCTION__);
  DlgAbstract::OnInitDialog();

  AddAnchor(IDOK,               __RDA_RB);
  AddAnchor(IDCANCEL,           __RDA_RB);
  AddAnchor(IDC_WMR_SHTAPIK,    __RDA_LB);
  AddAnchor(IDC_GRID, __RDA_LT, __RDA_RB);

  EnableSaveRestore("Resizable forms", m_eWMType == e_Profile? "DlgWriteMaterRule_Prof" : "DlgWriteMaterRule");
  return Init_Grid();
}

bool DlgWriteMaterRule::Init_Grid()
{
  try
  {
    CWaitCursor   wait;
    CStringArray  saOut, saSave;
    CString       sSQL;
    CMainFrame  *pMF = theApp.GetMainFrame();

    m_Grid.m_sDelConfirm = "Р Р€Р Т‘Р В°Р В»Р С‘РЎвЂљРЎРЉ Р С—РЎР‚Р В°Р Р†Р С‘Р В»Р С• РЎРѓР С—Р С‘РЎРѓР В°Р Р…Р С‘РЎРЏ?";
    m_Grid.SetAbleInsert (TRUE);
    m_Grid.m_Recordset->CursorLocation = adUseClient;

    if ( m_eWMType == e_Profile )
      sSQL.Format("select WriteMaterRule.*, "
                  "dbo.f_GetCriterionListWriteRule(WriteMaterRule.ID) as CriterionExist "
                  "from WriteMaterRule "
                  "  left outer join Material on WriteMaterRule.idMaterial = Material.ID "
                  "where idProfile = %li "
                  "order by nClass, Material.Name, idManufacter, idWidthType, idColor, nWriteType", m_idProfile);
    else
    if ( m_eWMType == e_Glass )
    {
                          sSQL.Format("select WMR.*, "
                  "  Product.Name  as ProdName, "
                  "  Product.Type  as ProdType, "
                  "  dbo.f_GetCriterionListWriteRule(WMR.ID) as CriterionExist, "
                  "  MaterGroup.nType as nTypeMG "
                  "from WriteMaterRule WMR "
                  "  inner join MaterGroup   on MaterGroup.ID = WMR.idMaterGroup "
                  "  left  join Product      on WMR.idProduct = Product.ID "
                  "  left  join GlassPack GP on GP.ID         = WMR.idGlassPack "                    "where idGlass != 0  or  idGlassFrame != 0  or  idGlassPack != 0  or  GP_Width != 0  or  idProfSys != 0 or nWriteType = 5 or (IsNull(idColor, 0) != 0 and (IsNull(idWidthType, 0) != 0)) "
                                                      "order by nType, IsNull(GP.Name, ''), idGlassPack, idProfSys, GP_Width, idWidthType, idColor");

            GetDlgItem(IDC_WMR_SHTAPIK)->ShowWindow(true);
      m_Grid.SetListMode();     }
    else
    if ( m_eWMType == e_ProfileDist )
      sSQL.Format("select WriteMaterRule.*, "
                  "dbo.f_GetCriterionListWriteRule(WriteMaterRule.ID) as CriterionExist "
                  "from WriteMaterRule "
                  "  left outer join Material on WriteMaterRule.idMaterial = Material.ID "
                  "where idProfileDist = %li "
                  "order by nClass, Material.Name, idManufacter, idWidthType, idColor, nWriteType", m_idProfile);

    m_Grid.OpenUpdateBatch(_bstr_t(sSQL), pMF->m_Conn.GetInterfacePtr());
    m_Grid.SetRecordsetProperty("Unique Table", "WriteMaterRule");

        if ( m_eWMType == e_Glass )
    {
            CADOGridLinkFieldMaster  *pGlass = new CADOGridLinkFieldMaster("Р РЋРЎвЂљР ВµР С”Р В»Р С•", "idGlass", "ID", "Name");
      RecordsetOpenReadOpt(pGlass->m_Recordset, "select ID, Name from Glass where Name is not NULL order by Name", pMF->m_Conn.GetInterfacePtr());
      if ( IsEmpty(pGlass->m_Recordset) )
      {
        theApp.MessageBox("Р РЋР С—РЎР‚Р В°Р Р†Р С•РЎвЂЎР Р…Р С‘Р С” РЎРѓРЎвЂљР ВµР С”Р С•Р В» Р Р…Р Вµ Р В·Р В°Р С—Р С•Р В»Р Р…Р ВµР Р…. Р СџРЎР‚Р С•Р Р†Р ВµРЎР‚РЎРЉРЎвЂљР Вµ Р С—РЎР‚Р В°Р Р†Р С‘Р В»РЎРЉР Р…Р С•РЎРѓРЎвЂљРЎРЉ Р Р…Р В°РЎРѓРЎвЂљРЎР‚Р С•Р в„–Р С”Р С‘.");
        return FALSE;
      }
      pGlass->SetComboBox(true);
      pGlass->SetEnableNULL(true, true, "");
      pGlass->SetFindDefaultVal (false);
      m_Grid.AddField (pGlass);
                  CADOGridLinkFieldMaster  *pGlassFrame = new CADOGridLinkFieldMaster("Р В Р В°Р СР С”Р В°", "idGlassFrame", "ID", "Name");
      RecordsetOpenReadOpt(pGlassFrame->m_Recordset, "select ID, Name from GlassFrame where Name is not NULL order by Name", pMF->m_Conn.GetInterfacePtr());
      if ( IsEmpty(pGlassFrame->m_Recordset) )
      {
        theApp.MessageBox("Р РЋР С—РЎР‚Р В°Р Р†Р С•РЎвЂЎР Р…Р С‘Р С” РЎР‚Р В°Р СР С•Р С” Р Р…Р Вµ Р В·Р В°Р С—Р С•Р В»Р Р…Р ВµР Р…. Р СџРЎР‚Р С•Р Р†Р ВµРЎР‚РЎРЉРЎвЂљР Вµ Р С—РЎР‚Р В°Р Р†Р С‘Р В»РЎРЉР Р…Р С•РЎРѓРЎвЂљРЎРЉ Р Р…Р В°РЎРѓРЎвЂљРЎР‚Р С•Р в„–Р С”Р С‘.");
        return FALSE;
      }
      pGlassFrame->SetComboBox(true);
      pGlassFrame->SetEnableNULL(true, true, "");
      pGlassFrame->SetFindDefaultVal (false);
      m_Grid.AddField (pGlassFrame);
                  CADOGridLinkFieldMaster  *pGlassPack = new CADOGridLinkFieldMaster("Р РЋРЎвЂљР ВµР С”Р В»Р С•Р С—Р В°Р С”Р ВµРЎвЂљ", "idGlassPack", "ID", "Name");
      RecordsetOpenReadOpt(pGlassPack->m_Recordset, "select ID, Name from GlassPack where Name is not NULL order by bUse desc, Name", pMF->m_Conn.GetInterfacePtr());
      if ( IsEmpty(pGlassPack->m_Recordset) )
      {
        theApp.MessageBox("Р РЋР С—РЎР‚Р В°Р Р†Р С•РЎвЂЎР Р…Р С‘Р С” РЎРѓРЎвЂљР ВµР С”Р В»Р С•Р С—Р В°Р С”Р ВµРЎвЂљР С•Р Р† Р Р…Р Вµ Р В·Р В°Р С—Р С•Р В»Р Р…Р ВµР Р…. Р СџРЎР‚Р С•Р Р†Р ВµРЎР‚РЎРЉРЎвЂљР Вµ Р С—РЎР‚Р В°Р Р†Р С‘Р В»РЎРЉР Р…Р С•РЎРѓРЎвЂљРЎРЉ Р Р…Р В°РЎРѓРЎвЂљРЎР‚Р С•Р в„–Р С”Р С‘.");
        return FALSE;
      }
      pGlassPack->SetComboBox(true);
      pGlassPack->SetEnableNULL(true, true, "");
      pGlassPack->SetFindDefaultVal (false);
      m_Grid.AddField (pGlassPack);
                  m_Grid.AddField ("Р СћР С•Р В»РЎвЂ°Р С‘Р Р…Р В° Р РЋР Сџ", "GP_Width");
                  CADOGridLinkFieldMaster  *pProfSys = new CADOGridLinkFieldMaster("Р РЋР С‘РЎРѓ. Р СџРЎР‚Р С•РЎвЂћ.", "idProfSys", "ID", "Name");
      RecordsetOpenReadOpt(pProfSys->m_Recordset, "select ID, Name from ProfSys where IsNull(bAccessories, 0) != 1 order by Name", pMF->m_Conn.GetInterfacePtr());
      if ( IsEmpty(pProfSys->m_Recordset) )
      {
        theApp.MessageBox("Р РЋР С—РЎР‚Р В°Р Р†Р С•РЎвЂЎР Р…Р С‘Р С” РЎРѓР С‘РЎРѓРЎвЂљР ВµР С Р С—РЎР‚Р С•РЎвЂћР С‘Р В»Р ВµР в„– Р Р…Р Вµ Р В·Р В°Р С—Р С•Р В»Р Р…Р ВµР Р…. Р СџРЎР‚Р С•Р Р†Р ВµРЎР‚РЎРЉРЎвЂљР Вµ Р С—РЎР‚Р В°Р Р†Р С‘Р В»РЎРЉР Р…Р С•РЎРѓРЎвЂљРЎРЉ Р Р…Р В°РЎРѓРЎвЂљРЎР‚Р С•Р в„–Р С”Р С‘.");
        return FALSE;
      }
      pProfSys->SetComboBox  (true);
      pProfSys->SetEnableNULL(true, true, "");
      pProfSys->SetFindDefaultVal(false);
      m_Grid.AddField (pProfSys);
                  CADOGridLinkFieldMaster *pShtapikType = new CADOGridLinkFieldMaster("Р СћР С‘Р С— РЎв‚¬РЎвЂљР В°Р С—Р С‘Р С”Р В°", "idShtapikType", "ID", "Name");
      RecordsetOpenReadOpt(pShtapikType->m_Recordset, "select ID, Name from ShtapikType order by Name", pMF->m_Conn.GetInterfacePtr());
      pShtapikType->SetComboBox  (true);
      pShtapikType->SetEnableNULL(true, true, "");
      pShtapikType->SetFindDefaultVal(false);
      m_Grid.AddField(pShtapikType);
    }
            saOut.RemoveAll();
    saSave.RemoveAll();

    if ( m_eWMType == e_Glass )
            sSQL = "select * from MaterGroup where nType in(2, 4, 6, 8, 9, 11, 16)";
    else
      sSQL = "select * from MaterGroup";
    _RecordsetPtr  rc(__uuidof (Recordset));
    RecordsetOpenReadOpt(rc, (_bstr_t)sSQL, pMF->m_Conn.GetInterfacePtr());
    if ( !IsEmpty(rc) )
      for (rc->MoveFirst(); !rc->adoEOF; rc->MoveNext())
      {
        saSave.Add(ConvertString(rc, "ID"  ));
        saOut. Add(ConvertString(rc, "Name"));
      }
    if ( rc->GetState() == adStateOpen )
      rc->Close();

    CADOGridLinkField  *pGroup = new CADOGridLinkField ("Р вЂњРЎР‚РЎС“Р С—Р С—Р В°", "idMaterGroup", saOut, saSave);
    pGroup->SetComboBox(true);
    m_Grid.AddField (pGroup);
            saOut.RemoveAll();
    saSave.RemoveAll();
    if ( m_eWMType != e_ProfileDist )
    {
      saSave.Add ( "1");   saOut.Add ("Р СџР В»Р С•РЎвЂ°Р В°Р Т‘РЎРЉ Р С”Р С•Р Р…РЎвЂљРЎС“РЎР‚Р В°, Р С”Р Р†.Р С"           );
      saSave.Add ( "2");   saOut.Add ("Р РЋР В°Р СРЎвЂ№Р в„– Р Т‘Р В»Р С‘Р Р…Р Р…РЎвЂ№Р в„– РЎРѓР ВµР С–Р СР ВµР Р…РЎвЂљ Р С”Р С•Р Р…РЎвЂљРЎС“РЎР‚Р В°, Р С");
      saSave.Add ( "4");   saOut.Add ("Р РЃРЎвЂљРЎС“Р С”Р С‘ Р Р…Р В° Р С”Р С•Р Р…РЎвЂљРЎС“РЎР‚"                 );
      saSave.Add ("13");   saOut.Add ("Р РЃРЎвЂљРЎС“Р С”Р В° Р Р…Р В° Р С”Р В°Р В¶Р Т‘РЎвЂ№Р Вµ N Р СР С РЎРѓР ВµР С–Р СР ВµР Р…РЎвЂљР В°"   );
      saSave.Add ("23");   saOut.Add ("Р РЃРЎвЂљРЎС“Р С”Р С‘ Р Р…Р В° РЎРѓР ВµР С–Р СР ВµР Р…РЎвЂљ"                );        saSave.Add ("12");   saOut.Add ("Р РЃРЎвЂљРЎС“Р С”Р С‘ Р Р…Р В° Р Р†Р ВµРЎР‚РЎвЂљ. РЎРѓР ВµР С–Р СР ВµР Р…РЎвЂљРЎвЂ№ Р С”Р С•Р Р…РЎвЂљРЎС“РЎР‚Р В°" );
      saSave.Add ("25");   saOut.Add ("Р РЃРЎвЂљРЎС“Р С”Р С‘ Р Р…Р В° Р С–Р С•РЎР‚Р С‘Р В·. РЎРѓР ВµР С–Р СР ВµР Р…РЎвЂљРЎвЂ№ Р С”Р С•Р Р…РЎвЂљРЎС“РЎР‚Р В°");
      saSave.Add ("15");   saOut.Add ("Р СџР ВµРЎР‚Р С‘Р СР ВµРЎвЂљРЎР‚ Р С•Р В±РЎвЂ°Р С‘Р в„–, Р С"               );

      if ( m_eWMType != e_Glass )       {
        saSave.Add("3");
        saOut.Add ("Р вЂќР В»Р С‘Р Р…РЎС“ Р С”Р В°Р В¶Р Т‘Р С•Р С–Р С• РЎРѓР ВµР С–Р СР ВµР Р…РЎвЂљР В°, Р С");
      }
      saSave.Add ("11");   saOut.Add ("Р РЃР С‘РЎР‚Р С‘Р Р…РЎС“ Р С”Р С•Р Р…РЎвЂљРЎС“РЎР‚Р В°, Р С"                         );
      saSave.Add ("60");   saOut.Add ("Р вЂ™РЎвЂ№РЎРѓР С•РЎвЂљРЎС“ Р С”Р С•Р Р…РЎвЂљРЎС“РЎР‚Р В°, Р С"                         );        saSave.Add ("52");   saOut.Add ("Р вЂќР В»Р С‘Р Р…РЎС“ Р Р†Р ВµРЎР‚РЎвЂљР С‘Р С”Р В°Р В»РЎРЉР Р…РЎвЂ№РЎвЂ¦ РЎРѓР ВµР С–Р СР ВµР Р…РЎвЂљР С•Р Р†, Р С"           );        saSave.Add ("53");   saOut.Add ("Р РЃРЎвЂљРЎС“Р С”Р С‘ Р Р…Р В° РЎРѓР С•Р ВµР Т‘. РЎРѓ РЎР‚Р В°Р СР С•Р в„– Р С—Р С•Р Т‘ 90Р’В°, РЎв‚¬РЎвЂљ."       );        saSave.Add ("54");   saOut.Add ("Р РЃРЎвЂљРЎС“Р С”Р С‘ Р Р…Р В° РЎРѓР С•Р ВµР Т‘. РЎРѓ РЎР‚Р В°Р СР С•Р в„– Р Р…Р Вµ Р С—Р С•Р Т‘ 90Р’В°, РЎв‚¬РЎвЂљ."    );        saSave.Add ("55");   saOut.Add ("Р РЃРЎвЂљРЎС“Р С”Р С‘ Р Р…Р В° РЎРѓР С•Р ВµР Т‘. РЎРѓР С• РЎРѓРЎвЂљР Р†Р С•РЎР‚Р С”Р С•Р в„– Р С—Р С•Р Т‘ 90Р’В°, РЎв‚¬РЎвЂљ."   );        saSave.Add ("56");   saOut.Add ("Р РЃРЎвЂљРЎС“Р С”Р С‘ Р Р…Р В° РЎРѓР С•Р ВµР Т‘. РЎРѓР С• РЎРѓРЎвЂљР Р†Р С•РЎР‚Р С”Р С•Р в„– Р Р…Р Вµ Р С—Р С•Р Т‘ 90Р’В°, РЎв‚¬РЎвЂљ.");        saSave.Add ("57");   saOut.Add ("Р РЃРЎвЂљРЎС“Р С”Р С‘ Р Р…Р В° РЎРѓР С•Р ВµР Т‘. РЎРѓ Р С‘Р СР С—Р С•РЎРѓРЎвЂљР С•Р С Р С—Р С•Р Т‘ 90Р’В°, T-Р С•Р В±РЎР‚ РЎв‚¬РЎвЂљ."   );        saSave.Add ("58");   saOut.Add ("Р РЃРЎвЂљРЎС“Р С”Р С‘ Р Р…Р В° РЎРѓР С•Р ВµР Т‘. РЎРѓ Р С‘Р СР С—Р С•РЎРѓРЎвЂљР С•Р С Р Р…Р Вµ Р С—Р С•Р Т‘ 90Р’В°, Р Сћ-Р С•Р В±РЎР‚ РЎв‚¬РЎвЂљ.");  
      saSave.Add ("59");   saOut.Add ("Р РЃРЎвЂљРЎС“Р С”Р С‘ Р Р…Р В° РЎРѓР С•Р ВµР Т‘. РЎРѓ Р С‘Р СР С—Р С•РЎРѓРЎвЂљР С•Р С Р С™РЎР‚Р ВµРЎРѓРЎвЂљ-Р С•Р В±РЎР‚. РЎв‚¬РЎвЂљ."  );  
      saSave.Add ("24");   saOut.Add ("Р РЃР С‘РЎР‚Р С‘Р Р…РЎС“ РЎР‚Р В°Р СРЎвЂ№, Р С"                            );              saSave.Add ("17");   saOut.Add ("Р СџРЎР‚РЎРЏР СР С•Р в„– РЎС“Р С–Р С•Р В», РЎв‚¬РЎвЂљ."                          );        saSave.Add ("18");   saOut.Add ("Р С™Р С•РЎРѓР С•Р в„– РЎС“Р С–Р С•Р В», РЎв‚¬РЎвЂљ."                           );        saSave.Add ("19");   saOut.Add ("Р С™Р С•Р В»-Р Р†Р С• РЎРѓР Т‘Р Р†Р С‘Р В¶Р Р…РЎвЂ№РЎвЂ¦ РЎРѓРЎвЂљР Р†Р С•РЎР‚Р С•Р С”, РЎв‚¬РЎвЂљ."              );        saSave.Add ("20");   saOut.Add ("Р РЋР С•Р ВµР Т‘Р С‘Р Р…Р ВµР Р…Р С‘Р Вµ РЎРѓ РЎР‚Р В°Р СР С•Р в„–, РЎв‚¬РЎвЂљ."                   );        saSave.Add ("21");   saOut.Add ("Р РЋР С•Р ВµР Т‘Р С‘Р Р…Р ВµР Р…Р С‘Р Вµ РЎРѓР С• РЎРѓРЎвЂљР Р†Р С•РЎР‚Р С”Р С•Р в„–, РЎв‚¬РЎвЂљ."               );        saSave.Add ("16");   saOut.Add ("Р РЋР С•Р ВµР Т‘Р С‘Р Р…Р ВµР Р…Р С‘Р Вµ РЎРѓ Р С‘Р СР С—Р С•РЎРѓРЎвЂљР С•Р С, РЎв‚¬РЎвЂљ."                );        saSave.Add ("26");   saOut.Add ("Р С›Р В±РЎР‰Р ВµР С”РЎвЂљ Р Р† РЎР‚Р В°Р СР Вµ Р С—Р С• РЎРѓР ВµР С–Р СР ВµР Р…РЎвЂљР В°Р С, Р С"             );        saSave.Add ("27");   saOut.Add ("Р С›Р В±РЎР‰Р ВµР С”РЎвЂљ Р Р† РЎРѓРЎвЂљР Р†Р С•РЎР‚Р С”Р Вµ Р С—Р С• РЎРѓР ВµР С–Р СР ВµР Р…РЎвЂљР В°Р С, Р С"          );        saSave.Add ("22");   saOut.Add ("Р вЂ™РЎвЂ№РЎРѓР С•РЎвЂљРЎС“ РЎРѓР Т‘Р Р†Р С‘Р В¶Р Р…РЎвЂ№РЎвЂ¦ РЎРѓРЎвЂљР Р†Р С•РЎР‚Р С•Р С” Р С•РЎвЂљ Р С‘РЎвЂ¦ Р С”Р С•Р В»-Р Р†Р В°, Р С"   );        saSave.Add ("28");   saOut.Add ("Р С™Р С•Р В»-Р Р†Р С• Р С—РЎР‚Р С‘ Р Р…Р В°Р В»Р С‘РЎвЂЎР С‘Р С‘ Р С—Р С•РЎР‚Р С•Р С–Р В°, РЎв‚¬РЎвЂљ."            );        saSave.Add ("29");   saOut.Add ("Р В¤Р С‘Р С”РЎРѓР С‘РЎР‚Р С•Р Р†Р В°Р Р…Р Р…РЎС“РЎР‹ Р Т‘Р В»Р С‘Р Р…РЎС“, Р С"                    );  
            saSave.Add ("30");   saOut.Add ("Р СџР С•Р В»Р С•РЎвЂљР Р…Р С• РЎР‚Р С•Р В»Р ВµРЎвЂљР В° Р С—Р С• РЎРѓР ВµР С–Р СР ВµР Р…РЎвЂљР В°Р С");              saSave.Add ("31");   saOut.Add ("Р вЂ™РЎвЂ№РЎРѓР С•РЎвЂљР В° Р С™Р С•Р Р…РЎвЂљРЎС“РЎР‚Р В° (Р С™), Р С");                    saSave.Add ("32");   saOut.Add ("Р РЃРЎвЂљ. Р Р…Р В° Р С—Р С•Р В»Р С•РЎвЂљР Р…Р С• РЎР‚Р С•Р В»Р ВµРЎвЂљР В° Р С—Р С• РЎРѓР ВµР С–Р СР ВµР Р…РЎвЂљР В°Р С");       saSave.Add ("33");   saOut.Add ("Р РЃР С‘РЎР‚Р С‘Р Р…Р В° Р С™Р С•Р Р…РЎвЂљРЎС“РЎР‚Р В° (Р С™), Р С");                          saSave.Add ("35");   saOut.Add ("Р РЃРЎвЂљРЎС“Р С”Р С‘ Р Р…Р В° Р С™Р С•Р Р…РЎвЂљРЎС“РЎР‚ (Р С™), Р С—Р С• РЎС“РЎРѓР В»Р С•Р Р†Р С‘РЎР‹ Р СџР В»Р С•РЎвЂ°Р В°Р Т‘РЎРЉ");             saSave.Add ("36");   saOut.Add ("Р вЂ™РЎвЂ№РЎРѓР С•РЎвЂљР В° Р С™Р С•Р Р…РЎвЂљРЎС“РЎР‚Р В° (Р С™), Р С, Р С—Р С• РЎС“РЎРѓР В»Р С•Р Р†Р С‘РЎР‹ Р вЂ™РЎвЂ№РЎРѓР С•РЎвЂљР В°");        saSave.Add ("37");   saOut.Add ("Р РЃР С‘РЎР‚Р С‘Р Р…Р В° Р С™Р С•Р Р…РЎвЂљРЎС“РЎР‚Р В° (Р С™), Р С, Р С—Р С• РЎС“РЎРѓР В»Р С•Р Р†Р С‘РЎР‹ Р РЃР С‘РЎР‚Р С‘Р Р…Р В°");        saSave.Add ("38");   saOut.Add ("Р РЃРЎвЂљРЎС“Р С”Р С‘ Р Р…Р В° Р С™Р С•Р Р…РЎвЂљРЎС“РЎР‚ (Р С™), Р С—Р С• РЎС“РЎРѓР В»Р С•Р Р†Р С‘РЎР‹ Р вЂ™РЎвЂ№РЎРѓР С•РЎвЂљР В°");          saSave.Add ("39");   saOut.Add ("Р РЃРЎвЂљРЎС“Р С”Р С‘ Р Р…Р В° Р С™Р С•Р Р…РЎвЂљРЎС“РЎР‚ (Р С™), Р С—Р С• РЎС“РЎРѓР В»Р С•Р Р†Р С‘РЎР‹ Р РЃР С‘РЎР‚Р С‘Р Р…Р В°");          saSave.Add ("40");   saOut.Add ("Р вЂ™РЎвЂ№РЎРѓР С•РЎвЂљР В° Р С™Р С•Р Р…РЎвЂљРЎС“РЎР‚Р В° (Р С™), Р С, Р С—Р С• РЎС“РЎРѓР В»Р С•Р Р†Р С‘РЎР‹ Р СџР В»Р С•РЎвЂ°Р В°Р Т‘РЎРЉ");       saSave.Add ("41");   saOut.Add ("Р РЃР С‘РЎР‚Р С‘Р Р…Р В° Р С™Р С•Р Р…РЎвЂљРЎС“РЎР‚Р В° (Р С™), Р С, Р С—Р С• РЎС“РЎРѓР В»Р С•Р Р†Р С‘РЎР‹ Р СџР В»Р С•РЎвЂ°Р В°Р Т‘РЎРЉ");       saSave.Add ("42");   saOut.Add ("Р РЃРЎвЂљРЎС“Р С”Р С‘ Р Р…Р В° Р С”Р В°Р В¶Р Т‘РЎвЂ№Р Вµ N Р СР С РЎв‚¬Р С‘РЎР‚Р С‘Р Р…РЎвЂ№");
      saSave.Add ("43");   saOut.Add ("Р вЂ™РЎвЂ№РЎРѓР С•РЎвЂљР В° Р С™Р С•Р Р…РЎвЂљРЎС“РЎР‚Р В° (Р С™), Р С, Р С—Р С• РЎС“РЎРѓР В»Р С•Р Р†Р С‘РЎР‹ Р РЃР С‘РЎР‚Р С‘Р Р…Р В°");        saSave.Add ("44");   saOut.Add ("Р РЃР С‘РЎР‚Р С‘Р Р…Р В° Р С™Р С•Р Р…РЎвЂљРЎС“РЎР‚Р В° (Р С™), Р С, Р С—Р С• РЎС“РЎРѓР В»Р С•Р Р†Р С‘РЎР‹ Р вЂ™РЎвЂ№РЎРѓР С•РЎвЂљР В°");        saSave.Add ("45");   saOut.Add ("Р СџР ВµРЎР‚Р С‘Р СР ВµРЎвЂљРЎР‚ Р С•Р В±РЎвЂ°Р С‘Р в„–(Р С™), Р С"           );                 saSave.Add ("46");   saOut.Add ("Р РЋР В°Р СРЎвЂ№Р в„– Р Т‘Р В»Р С‘Р Р…Р Р…РЎвЂ№Р в„– РЎРѓР ВµР С–Р СР ВµР Р…РЎвЂљ Р С”Р С•Р Р…РЎвЂљРЎС“РЎР‚Р В°(Р С™), Р С");

      if ( m_eWMType != e_Glass )
      {
        saSave.Add ("50");  saOut.Add ("Р вЂќР В»Р С‘Р Р…РЎС“ РЎРѓР ВµР С–Р С. Р СР ВµРЎвЂљР В°Р В»Р В»Р В° Р Т‘Р В»РЎРЏ Р С—Р В»Р В°РЎРѓРЎвЂљР С‘Р С”Р В° 45Р’В°;90Р’В°, Р С");
        saSave.Add ("51");  saOut.Add ("Р вЂќР В»Р С‘Р Р…РЎС“ РЎРѓР ВµР С–Р С. Р СР ВµРЎвЂљР В°Р В»Р В»Р В° Р Т‘Р В»РЎРЏ Р С—Р В»Р В°РЎРѓРЎвЂљР С‘Р С”Р В° 45Р’В°;45Р’В°, Р С");
      }
    }
    else
    if ( m_eWMType == e_ProfileDist )        {
      saSave.Add ("48");   saOut.Add ("Р РЃРЎвЂљРЎС“Р С”Р С‘ Р Р…Р В° РЎРѓР С•Р ВµР Т‘Р С‘Р Р…Р ВµР Р…Р С‘Р Вµ, РЎв‚¬РЎвЂљ");
      saSave.Add ("49");   saOut.Add ("Р вЂќР В»Р С‘Р Р…РЎС“ Р Р†Р ВµРЎР‚РЎвЂљР С‘Р С”.РЎРЊР В»Р ВµР СР ВµР Р…РЎвЂљР В° РЎРѓР С•Р ВµР Т‘Р С‘Р Р…Р ВµР Р…Р С‘РЎРЏ, Р С");
    }

    if ( m_eWMType == e_Glass )
    {
      saSave.Add ( "5"); saOut.Add ("Р СџР ВµРЎР‚Р ВµРЎРѓР ВµРЎвЂЎ.90 Р С–РЎР‚Р В°Р Т‘." );
      saSave.Add ( "6"); saOut.Add ("Р вЂќР В»Р С‘Р Р…РЎС“ Р вЂР С•Р В»РЎРЉРЎв‚¬.Р РЋРЎвЂљР С•РЎР‚.");
      saSave.Add ( "7"); saOut.Add ("Р РЃРЎвЂљ.Р В±Р ВµР В· Р С’РЎР‚Р С–Р С•Р Р…Р В°"    );
      saSave.Add ( "8"); saOut.Add ("Р РЃРЎвЂљ.РЎРѓ Р С’РЎР‚Р С–Р С•Р Р…Р С•Р С"     );
      saSave.Add ( "9"); saOut.Add ("Р СџР В»Р С•РЎвЂ°.Р В±Р ВµР В· Р С’РЎР‚Р С–Р С•Р Р…Р В°"  );
      saSave.Add ("10"); saOut.Add ("Р СџР В»Р С•РЎвЂ°.РЎРѓ Р С’РЎР‚Р С–Р С•Р Р…Р С•Р С"   );
      saSave.Add ("14"); saOut.Add ("Р СџР ВµРЎР‚Р С‘Р СР ВµРЎвЂљРЎР‚ Р С—Р С• РЎРѓР ВµР С–Р СР ВµР Р…РЎвЂљР В°Р С");
      saSave.Add ("47"); saOut.Add ("Р СџР ВµРЎР‚Р С‘Р СР ВµРЎвЂљРЎР‚ Р С—Р С• РЎРѓР ВµР С–Р СР ВµР Р…РЎвЂљР В°Р С(Р С™)");     }
    CADOGridLinkField  *pWriteTo = new CADOGridLinkField ("Р РЋР С—Р С‘РЎРѓР В°Р Р…Р С‘Р Вµ Р Р…Р В°", "nWriteType", saOut, saSave);
    pWriteTo->SetComboBox(true);
    m_Grid.AddField (pWriteTo);
            if ( m_eWMType == e_Glass )
    {
                  CADOGridLinkFieldMaster  *pWidthType = new CADOGridLinkFieldMaster("Р РЃР С‘РЎР‚Р С‘Р Р…Р В°", "idWidthType", "ID", "Name");
      RecordsetOpenReadOpt(pWidthType->m_Recordset, "select ID, Name, Width from WidthType order by Width", pMF->m_Conn.GetInterfacePtr());
      if ( IsEmpty(pWidthType->m_Recordset) )
      {
        theApp.MessageBox("Р РЋР С—РЎР‚Р В°Р Р†Р С•РЎвЂЎР Р…Р С‘Р С” Р РЃР С‘РЎР‚Р С‘Р Р…Р В° Р Р…Р Вµ Р В·Р В°Р С—Р С•Р В»Р Р…Р ВµР Р…. Р СџРЎР‚Р С•Р Р†Р ВµРЎР‚РЎРЉРЎвЂљР Вµ Р С—РЎР‚Р В°Р Р†Р С‘Р В»РЎРЉР Р…Р С•РЎРѓРЎвЂљРЎРЉ Р Р…Р В°РЎРѓРЎвЂљРЎР‚Р С•Р в„–Р С”Р С‘.");
        return FALSE;
      }
      pWidthType->SetComboBox (true);
      pWidthType->SetEnableNULL (true, false, " ");
      pWidthType->SetFindDefaultVal (false);
      m_Grid.AddField (pWidthType);
                  CADOGridLinkFieldMaster  *pColor = new CADOGridLinkFieldMaster("Р В¦Р Р†Р ВµРЎвЂљ", "idColor", "ID", "Name");
      RecordsetOpenReadOpt(pColor->m_Recordset, "select ID, Name from Color order by Name", pMF->m_Conn.GetInterfacePtr());
      if ( IsEmpty(pColor->m_Recordset) )
      {
        theApp.MessageBox("Р РЋР С—РЎР‚Р В°Р Р†Р С•РЎвЂЎР Р…Р С‘Р С” Р В¦Р Р†Р ВµРЎвЂљР С•Р Р† Р Р…Р Вµ Р В·Р В°Р С—Р С•Р В»Р Р…Р ВµР Р…. Р СџРЎР‚Р С•Р Р†Р ВµРЎР‚РЎРЉРЎвЂљР Вµ Р С—РЎР‚Р В°Р Р†Р С‘Р В»РЎРЉР Р…Р С•РЎРѓРЎвЂљРЎРЉ Р Р…Р В°РЎРѓРЎвЂљРЎР‚Р С•Р в„–Р С”Р С‘.");
        return FALSE;
      }
      pColor->SetComboBox (true);
      pColor->SetEnableNULL (true, false, " ");
      pColor->SetFindDefaultVal (false);
      m_Grid.AddField (pColor);
    }
            CADOGridLinkFieldMaster  *pMaterialName = new CADOGridLinkFieldMaster("Р СљР В°РЎвЂљР ВµРЎР‚Р С‘Р В°Р В»", "idMaterial", "ID", "Name");
    RecordsetOpenReadOpt(pMaterialName->m_Recordset, "select IsNull(Name, '') + ' ' + IsNull(Art,'') as Name, ID "
                                                     "from Material where Name is not NULL and nMaterType = 1", pMF->m_Conn.GetInterfacePtr());
    if ( IsEmpty(pMaterialName->m_Recordset) )
    {
      theApp.MessageBox("Р РЋР С—РЎР‚Р В°Р Р†Р С•РЎвЂЎР Р…Р С‘Р С” Р СљР В°РЎвЂљР ВµРЎР‚Р С‘Р В°Р В»Р С•Р Р† Р Р…Р Вµ Р В·Р В°Р С—Р С•Р В»Р Р…Р ВµР Р…. Р СџРЎР‚Р С•Р Р†Р ВµРЎР‚РЎРЉРЎвЂљР Вµ Р С—РЎР‚Р В°Р Р†Р С‘Р В»РЎРЉР Р…Р С•РЎРѓРЎвЂљРЎРЉ Р Р…Р В°РЎРѓРЎвЂљРЎР‚Р С•Р в„–Р С”Р С‘.");
      return FALSE;
    }
    pMaterialName->SetComboBox (false);
    pMaterialName->bEditable = false;
    m_Grid.AddField (pMaterialName);         m_Grid.AddField ("+ Р С” РЎР‚Р В°Р В·Р СР ВµРЎР‚РЎС“", "SizeAdd" );
    m_Grid.AddField ("+ Р С” РЎР‚Р В°Р В·Р С. X", "SizeAddX");
    m_Grid.AddField ("+ Р С” РЎР‚Р В°Р В·Р С. Y", "SizeAddY");

    saOut.RemoveAll();
    saSave.RemoveAll();
    sSQL = "select * from Norm order by Name";
    rc->Open ((_bstr_t)(LPCTSTR)sSQL, pMF->m_Conn.GetInterfacePtr(), adOpenStatic, adLockReadOnly, adCmdText);
    if ( !IsEmpty(rc) )
      for (rc->MoveFirst(); !rc->adoEOF; rc->MoveNext())
      {
        saSave.Add(ConvertString(rc, "ID"  ));
        saOut. Add(ConvertString(rc, "Name"));
      }
    if ( rc->GetState() == adStateOpen )
      rc->Close();


        if ( m_eWMType != e_Glass )
    {
      m_Grid.AddField ("Р С™Р С•РЎР‚РЎР‚Р ВµР С”РЎвЂ Р С‘РЎРЏ Р Р…Р С•РЎР‚Р СРЎвЂ№ +/-", "NormAdd");
    }

    CADOGridLinkField  * pNorm = new CADOGridLinkField ("Р СњР С•РЎР‚Р СР В°", "idNorm", saOut, saSave);
    pNorm->SetComboBox(true);
    m_Grid.AddField (pNorm);

    m_Grid.AddField ("Р С™Р С•Р В»-Р Р†Р С•", "nCount");

    CADOGridLinkField  *pCondition = new CADOGridLinkField("Р Р€РЎРѓР В»Р С•Р Р†Р С‘Р Вµ", "ConditionScript");
    m_Grid.AddField(pCondition);
    pCondition->SetButton(true);
    pCondition->BnClick = fnText;

    CADOGridLinkField  *pNumber = new CADOGridLinkField("Р В¤Р С•РЎР‚Р СРЎС“Р В»Р В° Р С™Р С•Р В»-Р Р†Р С•", "NumberScript");
    m_Grid.AddField(pNumber);
    pNumber->SetButton(true);
    pNumber->BnClick = fnText;

    CADOGridLinkField  * m_lbCriterion = new CADOGridLinkField("Р С™РЎР‚Р С‘РЎвЂљР ВµРЎР‚Р С‘Р С‘",  "CriterionExist");
    m_Grid.AddField(m_lbCriterion);
    m_lbCriterion->SetButton(true);
    m_lbCriterion->ReadOnly(true);
    if ( m_eWMType == e_Glass )
      m_lbCriterion->BnClick = fnSelCriterionGlass;
    else
      m_lbCriterion->BnClick = fnSelCriterionProf;
    m_lbCriterion->m_nFormatCell = DT_RIGHT|DT_VCENTER|DT_WORDBREAK|DT_SINGLELINE;
    m_lbCriterion->bEditable = false;
        
    if ( m_eWMType != e_Glass )
    {
            CADOGridLinkField  *pSetColor    = new CADOGridLinkField("Р СџРЎР‚Р С‘РЎРѓР Р†.Р В¦Р Р†Р ВµРЎвЂљ?",     "bSetColor"   );
      pSetColor->SetCheckBox(true);
      m_Grid.AddField(pSetColor);
            CADOGridLinkField  *pSetColorIns = new CADOGridLinkField("Р СџРЎР‚Р С‘РЎРѓР Р†.Р В¦Р Р†.Р вЂ™Р Р…РЎС“РЎвЂљРЎР‚?", "bSetColorIns");
      pSetColorIns->SetCheckBox(true);
      m_Grid.AddField(pSetColorIns);
            CADOGridLinkField  *pSetColorBase = new CADOGridLinkField("Р СџРЎР‚Р С‘РЎРѓР Р†.Р В¦Р Р†.Р С›РЎРѓР Р…?", "bSetColorBase");
      pSetColorBase->SetCheckBox(true);
      m_Grid.AddField(pSetColorBase);
            CADOGridLinkField  *pSetColorExt = new CADOGridLinkField("Р СџРЎР‚Р С‘РЎРѓР Р†.Р В¦Р Р†.Р вЂ™Р Р…Р ВµРЎв‚¬?",  "bSetColorExt");
      pSetColorExt->SetCheckBox(true);
      m_Grid.AddField(pSetColorExt);
            CADOGridLinkField  *pColorSwap = new CADOGridLinkField("Р СљР ВµР Р…РЎРЏРЎвЂљРЎРЉ Р вЂ™Р Р…РЎС“РЎвЂљ.Р В¦Р Р†.Р Р…Р В° Р вЂ™Р Р…Р ВµРЎв‚¬?", "bColorSwap");
      pColorSwap->SetCheckBox(true);
      m_Grid.AddField(pColorSwap);
    }         CADOGridLinkFieldMaster  *pColorGroup = new CADOGridLinkFieldMaster("Р вЂњРЎР‚РЎС“Р С—Р С—Р В° РЎвЂ Р Р†Р ВµРЎвЂљР С•Р Р†", "idColorGroup", "ID", "Name");
    RecordsetOpenReadOpt(pColorGroup->m_Recordset, "select ID, Name from ColorGroup order by Name", pMF->m_Conn.GetInterfacePtr());

    pColorGroup->SetComboBox (true);
    pColorGroup->SetEnableNULL (true, true, " ");
    pColorGroup->SetFindDefaultVal (false);
    m_Grid.AddField (pColorGroup);

    CADOGridLinkField  *pNotExecColorGroup = new CADOGridLinkField("Р С›РЎвЂљРЎР‚Р С‘РЎвЂ Р В°Р Р…Р С‘Р Вµ?", "bNotExecColorGroup");
    pNotExecColorGroup->SetCheckBox (true);
    m_Grid.AddField (pNotExecColorGroup);

    m_Grid.AddField ("Р РЃР В°Р С–", "Step");

    m_Grid.AddField ("Р СљР С‘Р Р….Р В·Р Р…Р В°РЎвЂЎ.",  "MinVal");
    m_Grid.AddField ("Р СљР В°Р С”РЎРѓ.Р В·Р Р…Р В°РЎвЂЎ.", "MaxVal");

    m_Grid.AddField ("Р вЂєР ВµР Р†РЎвЂ№Р в„– РЎС“Р С–Р С•Р В»",  "AngleLeft" );
    m_Grid.AddField ("Р СџРЎР‚Р В°Р Р†РЎвЂ№Р в„– РЎС“Р С–Р С•Р В»", "AngleRight");

    CADOGridLinkField  * pIsAdd = new CADOGridLinkField("Р вЂќР С•Р С—.Р С›Р С—Р ВµРЎР‚Р В°РЎвЂ Р С‘РЎРЏ", "IsAdd");
    pIsAdd->SetCheckBox (true);
    m_Grid.AddField (pIsAdd);

    if ( m_eWMType == e_Glass )
    {
            CADOGridLinkField  *pSetColorBase = new CADOGridLinkField("Р СџРЎР‚Р С‘РЎРѓР Р†.Р В¦Р Р†.Р С›РЎРѓР Р…?", "bSetColorBase");
      pSetColorBase->SetCheckBox(true);
      m_Grid.AddField(pSetColorBase);
    }
    else
    {
      CADOGridLinkFieldMaster  *pTypeMontage = new CADOGridLinkFieldMaster ("Р СћР С‘Р С— Р СР С•Р Р…РЎвЂљР В°Р В¶Р В°", "idTypeMontage", "ID", "Name", true);
      sSQL = "select "
             "  ID, "
             "  Name + case when IsNull(bWriteToMontageProject, 0) = 1 then ' (РЎРѓР С—Р С‘РЎРѓ. Р Р…Р В° Р СР С•Р Р…РЎвЂљР В°Р В¶Р Р…РЎвЂ№Р Вµ РЎР‚Р В°Р В±Р С•РЎвЂљРЎвЂ№)' else '' end as Name "
             "from TypeMontage "
             "order by ID";
      RecordsetOpenReadOpt(pTypeMontage->m_Recordset, (_bstr_t)sSQL, pMF->m_Conn.GetInterfacePtr());
      pTypeMontage->SetComboBox(true);
      m_Grid.AddField(pTypeMontage);
    }

    m_Grid.Init();

    if ( m_Grid.GetViewColNum ("CriterionExist") != -1 )
      m_Grid.AutoSizeColumn(m_Grid.GetViewColNum ("CriterionExist"));

    if ( !m_Grid.IsEmpty() )
      m_Grid.Select_Cur_First();

    pMF->SetupRefPermissions(m_Grid);
  }
  CATCH_SHOW(__FILE__, __LINE__, __FUNCTION__)
  return TRUE;
}

void DlgWriteMaterRule::OnBnClickedOk()
{
  try
  {
        m_Grid.UpdateBatch();
  }
  CATCH_HIDE(__FILE__, __LINE__, __FUNCTION__)
  OnOK();
}

void DlgWriteMaterRule::OnBnClickedCancel()
{
  try
  {
    m_Grid.CancelBatch();
  }
  CATCH_SHOW(__FILE__, __LINE__, __FUNCTION__)
  OnCancel();
}

BOOL DlgWriteMaterRule::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
  try
  {
    if ( wParam == IDC_GRID )
    {
      NM_GRIDVIEW  *pGV = (NM_GRIDVIEW*)lParam;
      if ( pGV->hdr.code == NM_DBLCLK )
        m_Grid.ChangeMaterial();
    }
  }
  CATCH_SHOW(__FILE__, __LINE__, __FUNCTION__)
  return DlgAbstract::OnNotify(wParam, lParam, pResult);
}

void DlgWriteMaterRule::OnBnWMRShtapik()
{
  try
  {
    CString  sCaption;
    long     nTypeMG          = 0,
             idProfSys        = 0,
             idWriteMaterRule = 0;

     if ( m_Grid.GetGridModifyStatus() )
     {
        m_Grid.UpdateBatch();
        m_Grid.RequeryAll();
     }

    if ( m_Grid.Select_Cur()  &&  !m_Grid.IsEmpty() )
    {
      idProfSys = ConvertLong(m_Grid.m_Recordset, "idProfSys");
      long nGPWidth = ConvertLong(m_Grid.m_Recordset, "GP_Width");

      if ( idProfSys > 0 && nGPWidth > 0 )
      {
        idWriteMaterRule = ConvertLong(m_Grid.m_Recordset, "ID");
        DlgShtapikRule  Dlg(sCaption, this, idProfSys, idWriteMaterRule);
        Dlg.DoModal();
      }
      else if ( idProfSys == 0 )
       theApp.MessageBox("Р СњР Вµ Р В·Р В°Р Т‘Р В°Р Р…Р В° РЎРѓР С‘РЎРѓРЎвЂљР ВµР СР В° Р С—РЎР‚Р С•РЎвЂћР С‘Р В»Р ВµР в„–");
      else if ( nGPWidth == 0)
       theApp.MessageBox("Р СњР Вµ Р В·Р В°Р Т‘Р В°Р Р…Р В° РЎвЂљР С•Р В»РЎвЂ°Р С‘Р Р…Р В° РЎРѓРЎвЂљР ВµР С”Р В»Р С•Р С—Р В°Р С”Р ВµРЎвЂљР В°");
    }
    else
      theApp.MessageBox("Р СњР ВµР Р†Р С•Р В·Р СР С•Р В¶Р Р…Р С• Р Р…Р В°РЎРѓРЎвЂљРЎР‚Р С•Р С‘РЎвЂљРЎРЉ РЎРѓР С—Р С‘РЎРѓР В°Р Р…Р С‘Р Вµ Р Р…Р В° Р С—РЎР‚Р С•РЎвЂћР С‘Р В»РЎРЏ");
  }
  CATCH_SHOW(__FILE__, __LINE__, __FUNCTION__)
}

