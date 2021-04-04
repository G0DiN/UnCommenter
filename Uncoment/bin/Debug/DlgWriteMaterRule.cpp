#include "stdafx.h"
CArray<long, long> CRuleGrid::aList;

BEGIN_MESSAGE_MAP(CRuleGrid, CADOGridRecord)
 ON_WM_LBUTTONUP  ()
 ON_WM_CONTEXTMENU()
 ON_COMMAND       (IDC_COPY_PROF_WRITE,  OnCopyProfWriteWM )
 ON_COMMAND       (IDC_PASTE_PROF_WRITE, OnPasteProfWriteWM)
 ON_COMMAND       (ID_PROTOCOL_DEL_MI,   OnProtocolDel     )
END_MESSAGE_MAP()


_variant_t fnSelCriterionProf(int Row, int Col, _variant_t Val)
{
  long  id = Val.vt != VT_NULL ? long(Val) : 0;

  DlgCritSetForWMater  Dlg ("", id, e_idtype_idWriteMaterRule, NULL);
  Dlg.m_nMode = e_cmProf;

  long  res = 0;
  if ( Dlg.DoModal() == IDOK )
    res = Dlg.m_Grid.GetGridModifyStatus()? 1 : 0;

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
      ABMessageBox("РќРµ РІС‹РґРµР»РµРЅРѕ РЅРё РѕРґРЅРѕР№ СЃС‚СЂРѕРєРё!");
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

    m_Grid.m_sDelConfirm = "РЈРґР°Р»РёС‚СЊ РїСЂР°РІРёР»Рѕ СЃРїРёСЃР°РЅРёСЏ?";
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
            CADOGridLinkFieldMaster  *pGlass = new CADOGridLinkFieldMaster("РЎС‚РµРєР»Рѕ", "idGlass", "ID", "Name");
      RecordsetOpenReadOpt(pGlass->m_Recordset, "select ID, Name from Glass where Name is not NULL order by Name", pMF->m_Conn.GetInterfacePtr());
      if ( IsEmpty(pGlass->m_Recordset) )
      {
        theApp.MessageBox("РЎРїСЂР°РІРѕС‡РЅРёРє СЃС‚РµРєРѕР» РЅРµ Р·Р°РїРѕР»РЅРµРЅ. РџСЂРѕРІРµСЂСЊС‚Рµ РїСЂР°РІРёР»СЊРЅРѕСЃС‚СЊ РЅР°СЃС‚СЂРѕР№РєРё.");
        return FALSE;
      }
      pGlass->SetComboBox(true);
      pGlass->SetEnableNULL(true, true, "");
      pGlass->SetFindDefaultVal (false);
      m_Grid.AddField (pGlass);
                  CADOGridLinkFieldMaster  *pGlassFrame = new CADOGridLinkFieldMaster("Р Р°РјРєР°", "idGlassFrame", "ID", "Name");
      RecordsetOpenReadOpt(pGlassFrame->m_Recordset, "select ID, Name from GlassFrame where Name is not NULL order by Name", pMF->m_Conn.GetInterfacePtr());
      if ( IsEmpty(pGlassFrame->m_Recordset) )
      {
        theApp.MessageBox("РЎРїСЂР°РІРѕС‡РЅРёРє СЂР°РјРѕРє РЅРµ Р·Р°РїРѕР»РЅРµРЅ. РџСЂРѕРІРµСЂСЊС‚Рµ РїСЂР°РІРёР»СЊРЅРѕСЃС‚СЊ РЅР°СЃС‚СЂРѕР№РєРё.");
        return FALSE;
      }
      pGlassFrame->SetComboBox(true);
      pGlassFrame->SetEnableNULL(true, true, "");
      pGlassFrame->SetFindDefaultVal (false);
      m_Grid.AddField (pGlassFrame);
                  CADOGridLinkFieldMaster  *pGlassPack = new CADOGridLinkFieldMaster("РЎС‚РµРєР»РѕРїР°РєРµС‚", "idGlassPack", "ID", "Name");
      RecordsetOpenReadOpt(pGlassPack->m_Recordset, "select ID, Name from GlassPack where Name is not NULL order by bUse desc, Name", pMF->m_Conn.GetInterfacePtr());
      if ( IsEmpty(pGlassPack->m_Recordset) )
      {
        theApp.MessageBox("РЎРїСЂР°РІРѕС‡РЅРёРє СЃС‚РµРєР»РѕРїР°РєРµС‚РѕРІ РЅРµ Р·Р°РїРѕР»РЅРµРЅ. РџСЂРѕРІРµСЂСЊС‚Рµ РїСЂР°РІРёР»СЊРЅРѕСЃС‚СЊ РЅР°СЃС‚СЂРѕР№РєРё.");
        return FALSE;
      }
      pGlassPack->SetComboBox(true);
      pGlassPack->SetEnableNULL(true, true, "");
      pGlassPack->SetFindDefaultVal (false);
      m_Grid.AddField (pGlassPack);
                  m_Grid.AddField ("РўРѕР»С‰РёРЅР° РЎРџ", "GP_Width");
                  CADOGridLinkFieldMaster  *pProfSys = new CADOGridLinkFieldMaster("РЎРёСЃ. РџСЂРѕС„.", "idProfSys", "ID", "Name");
      RecordsetOpenReadOpt(pProfSys->m_Recordset, "select ID, Name from ProfSys where IsNull(bAccessories, 0) != 1 order by Name", pMF->m_Conn.GetInterfacePtr());
      if ( IsEmpty(pProfSys->m_Recordset) )
      {
        theApp.MessageBox("РЎРїСЂР°РІРѕС‡РЅРёРє СЃРёСЃС‚РµРј РїСЂРѕС„РёР»РµР№ РЅРµ Р·Р°РїРѕР»РЅРµРЅ. РџСЂРѕРІРµСЂСЊС‚Рµ РїСЂР°РІРёР»СЊРЅРѕСЃС‚СЊ РЅР°СЃС‚СЂРѕР№РєРё.");
        return FALSE;
      }
      pProfSys->SetComboBox  (true);
      pProfSys->SetEnableNULL(true, true, "");
      pProfSys->SetFindDefaultVal(false);
      m_Grid.AddField (pProfSys);
                  CADOGridLinkFieldMaster *pShtapikType = new CADOGridLinkFieldMaster("РўРёРї С€С‚Р°РїРёРєР°", "idShtapikType", "ID", "Name");
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

    CADOGridLinkField  *pGroup = new CADOGridLinkField ("Р“СЂСѓРїРїР°", "idMaterGroup", saOut, saSave);
    pGroup->SetComboBox(true);
    m_Grid.AddField (pGroup);
            saOut.RemoveAll();
    saSave.RemoveAll();
    if ( m_eWMType != e_ProfileDist )
    {
      saSave.Add ( "1");   saOut.Add ("РџР»РѕС‰Р°РґСЊ РєРѕРЅС‚СѓСЂР°, РєРІ.Рј"           );
      saSave.Add ( "2");   saOut.Add ("РЎР°РјС‹Р№ РґР»РёРЅРЅС‹Р№ СЃРµРіРјРµРЅС‚ РєРѕРЅС‚СѓСЂР°, Рј");
      saSave.Add ( "4");   saOut.Add ("РЁС‚СѓРєРё РЅР° РєРѕРЅС‚СѓСЂ"                 );
      saSave.Add ("13");   saOut.Add ("РЁС‚СѓРєР° РЅР° РєР°Р¶РґС‹Рµ N РјРј СЃРµРіРјРµРЅС‚Р°"   );
      saSave.Add ("23");   saOut.Add ("РЁС‚СѓРєРё РЅР° СЃРµРіРјРµРЅС‚"                );        saSave.Add ("12");   saOut.Add ("РЁС‚СѓРєРё РЅР° РІРµСЂС‚. СЃРµРіРјРµРЅС‚С‹ РєРѕРЅС‚СѓСЂР°" );
      saSave.Add ("25");   saOut.Add ("РЁС‚СѓРєРё РЅР° РіРѕСЂРёР·. СЃРµРіРјРµРЅС‚С‹ РєРѕРЅС‚СѓСЂР°");
      saSave.Add ("15");   saOut.Add ("РџРµСЂРёРјРµС‚СЂ РѕР±С‰РёР№, Рј"               );

      if ( m_eWMType != e_Glass )       {
        saSave.Add("3");
        saOut.Add ("Р”Р»РёРЅСѓ РєР°Р¶РґРѕРіРѕ СЃРµРіРјРµРЅС‚Р°, Рј");
      }
      saSave.Add ("11");   saOut.Add ("РЁРёСЂРёРЅСѓ РєРѕРЅС‚СѓСЂР°, Рј"                         );
      saSave.Add ("60");   saOut.Add ("Р’С‹СЃРѕС‚Сѓ РєРѕРЅС‚СѓСЂР°, Рј"                         );        saSave.Add ("52");   saOut.Add ("Р”Р»РёРЅСѓ РІРµСЂС‚РёРєР°Р»СЊРЅС‹С… СЃРµРіРјРµРЅС‚РѕРІ, Рј"           );        saSave.Add ("53");   saOut.Add ("РЁС‚СѓРєРё РЅР° СЃРѕРµРґ. СЃ СЂР°РјРѕР№ РїРѕРґ 90В°, С€С‚."       );        saSave.Add ("54");   saOut.Add ("РЁС‚СѓРєРё РЅР° СЃРѕРµРґ. СЃ СЂР°РјРѕР№ РЅРµ РїРѕРґ 90В°, С€С‚."    );        saSave.Add ("55");   saOut.Add ("РЁС‚СѓРєРё РЅР° СЃРѕРµРґ. СЃРѕ СЃС‚РІРѕСЂРєРѕР№ РїРѕРґ 90В°, С€С‚."   );        saSave.Add ("56");   saOut.Add ("РЁС‚СѓРєРё РЅР° СЃРѕРµРґ. СЃРѕ СЃС‚РІРѕСЂРєРѕР№ РЅРµ РїРѕРґ 90В°, С€С‚.");        saSave.Add ("57");   saOut.Add ("РЁС‚СѓРєРё РЅР° СЃРѕРµРґ. СЃ РёРјРїРѕСЃС‚РѕРј РїРѕРґ 90В°, T-РѕР±СЂ С€С‚."   );        saSave.Add ("58");   saOut.Add ("РЁС‚СѓРєРё РЅР° СЃРѕРµРґ. СЃ РёРјРїРѕСЃС‚РѕРј РЅРµ РїРѕРґ 90В°, Рў-РѕР±СЂ С€С‚.");  
      saSave.Add ("59");   saOut.Add ("РЁС‚СѓРєРё РЅР° СЃРѕРµРґ. СЃ РёРјРїРѕСЃС‚РѕРј РљСЂРµСЃС‚-РѕР±СЂ. С€С‚."  );  
      saSave.Add ("24");   saOut.Add ("РЁРёСЂРёРЅСѓ СЂР°РјС‹, Рј"                            );              saSave.Add ("17");   saOut.Add ("РџСЂСЏРјРѕР№ СѓРіРѕР», С€С‚."                          );        saSave.Add ("18");   saOut.Add ("РљРѕСЃРѕР№ СѓРіРѕР», С€С‚."                           );        saSave.Add ("19");   saOut.Add ("РљРѕР»-РІРѕ СЃРґРІРёР¶РЅС‹С… СЃС‚РІРѕСЂРѕРє, С€С‚."              );        saSave.Add ("20");   saOut.Add ("РЎРѕРµРґРёРЅРµРЅРёРµ СЃ СЂР°РјРѕР№, С€С‚."                   );        saSave.Add ("21");   saOut.Add ("РЎРѕРµРґРёРЅРµРЅРёРµ СЃРѕ СЃС‚РІРѕСЂРєРѕР№, С€С‚."               );        saSave.Add ("16");   saOut.Add ("РЎРѕРµРґРёРЅРµРЅРёРµ СЃ РёРјРїРѕСЃС‚РѕРј, С€С‚."                );        saSave.Add ("26");   saOut.Add ("РћР±СЉРµРєС‚ РІ СЂР°РјРµ РїРѕ СЃРµРіРјРµРЅС‚Р°Рј, Рј"             );        saSave.Add ("27");   saOut.Add ("РћР±СЉРµРєС‚ РІ СЃС‚РІРѕСЂРєРµ РїРѕ СЃРµРіРјРµРЅС‚Р°Рј, Рј"          );        saSave.Add ("22");   saOut.Add ("Р’С‹СЃРѕС‚Сѓ СЃРґРІРёР¶РЅС‹С… СЃС‚РІРѕСЂРѕРє РѕС‚ РёС… РєРѕР»-РІР°, Рј"   );        saSave.Add ("28");   saOut.Add ("РљРѕР»-РІРѕ РїСЂРё РЅР°Р»РёС‡РёРё РїРѕСЂРѕРіР°, С€С‚."            );        saSave.Add ("29");   saOut.Add ("Р¤РёРєСЃРёСЂРѕРІР°РЅРЅСѓСЋ РґР»РёРЅСѓ, Рј"                    );  
            saSave.Add ("30");   saOut.Add ("РџРѕР»РѕС‚РЅРѕ СЂРѕР»РµС‚Р° РїРѕ СЃРµРіРјРµРЅС‚Р°Рј");              saSave.Add ("31");   saOut.Add ("Р’С‹СЃРѕС‚Р° РљРѕРЅС‚СѓСЂР° (Рљ), Рј");                    saSave.Add ("32");   saOut.Add ("РЁС‚. РЅР° РїРѕР»РѕС‚РЅРѕ СЂРѕР»РµС‚Р° РїРѕ СЃРµРіРјРµРЅС‚Р°Рј");       saSave.Add ("33");   saOut.Add ("РЁРёСЂРёРЅР° РљРѕРЅС‚СѓСЂР° (Рљ), Рј");                          saSave.Add ("35");   saOut.Add ("РЁС‚СѓРєРё РЅР° РљРѕРЅС‚СѓСЂ (Рљ), РїРѕ СѓСЃР»РѕРІРёСЋ РџР»РѕС‰Р°РґСЊ");             saSave.Add ("36");   saOut.Add ("Р’С‹СЃРѕС‚Р° РљРѕРЅС‚СѓСЂР° (Рљ), Рј, РїРѕ СѓСЃР»РѕРІРёСЋ Р’С‹СЃРѕС‚Р°");        saSave.Add ("37");   saOut.Add ("РЁРёСЂРёРЅР° РљРѕРЅС‚СѓСЂР° (Рљ), Рј, РїРѕ СѓСЃР»РѕРІРёСЋ РЁРёСЂРёРЅР°");        saSave.Add ("38");   saOut.Add ("РЁС‚СѓРєРё РЅР° РљРѕРЅС‚СѓСЂ (Рљ), РїРѕ СѓСЃР»РѕРІРёСЋ Р’С‹СЃРѕС‚Р°");          saSave.Add ("39");   saOut.Add ("РЁС‚СѓРєРё РЅР° РљРѕРЅС‚СѓСЂ (Рљ), РїРѕ СѓСЃР»РѕРІРёСЋ РЁРёСЂРёРЅР°");          saSave.Add ("40");   saOut.Add ("Р’С‹СЃРѕС‚Р° РљРѕРЅС‚СѓСЂР° (Рљ), Рј, РїРѕ СѓСЃР»РѕРІРёСЋ РџР»РѕС‰Р°РґСЊ");       saSave.Add ("41");   saOut.Add ("РЁРёСЂРёРЅР° РљРѕРЅС‚СѓСЂР° (Рљ), Рј, РїРѕ СѓСЃР»РѕРІРёСЋ РџР»РѕС‰Р°РґСЊ");       saSave.Add ("42");   saOut.Add ("РЁС‚СѓРєРё РЅР° РєР°Р¶РґС‹Рµ N РјРј С€РёСЂРёРЅС‹");
      saSave.Add ("43");   saOut.Add ("Р’С‹СЃРѕС‚Р° РљРѕРЅС‚СѓСЂР° (Рљ), Рј, РїРѕ СѓСЃР»РѕРІРёСЋ РЁРёСЂРёРЅР°");        saSave.Add ("44");   saOut.Add ("РЁРёСЂРёРЅР° РљРѕРЅС‚СѓСЂР° (Рљ), Рј, РїРѕ СѓСЃР»РѕРІРёСЋ Р’С‹СЃРѕС‚Р°");        saSave.Add ("45");   saOut.Add ("РџРµСЂРёРјРµС‚СЂ РѕР±С‰РёР№(Рљ), Рј"           );                 saSave.Add ("46");   saOut.Add ("РЎР°РјС‹Р№ РґР»РёРЅРЅС‹Р№ СЃРµРіРјРµРЅС‚ РєРѕРЅС‚СѓСЂР°(Рљ), Рј");

      if ( m_eWMType != e_Glass )
      {
        saSave.Add ("50");  saOut.Add ("Р”Р»РёРЅСѓ СЃРµРіРј. РјРµС‚Р°Р»Р»Р° РґР»СЏ РїР»Р°СЃС‚РёРєР° 45В°;90В°, Рј");
        saSave.Add ("51");  saOut.Add ("Р”Р»РёРЅСѓ СЃРµРіРј. РјРµС‚Р°Р»Р»Р° РґР»СЏ РїР»Р°СЃС‚РёРєР° 45В°;45В°, Рј");
      }
    }
    else
    if ( m_eWMType == e_ProfileDist )        {
      saSave.Add ("48");   saOut.Add ("РЁС‚СѓРєРё РЅР° СЃРѕРµРґРёРЅРµРЅРёРµ, С€С‚");
      saSave.Add ("49");   saOut.Add ("Р”Р»РёРЅСѓ РІРµСЂС‚РёРє.СЌР»РµРјРµРЅС‚Р° СЃРѕРµРґРёРЅРµРЅРёСЏ, Рј");
    }

    if ( m_eWMType == e_Glass )
    {
      saSave.Add ( "5"); saOut.Add ("РџРµСЂРµСЃРµС‡.90 РіСЂР°Рґ." );
      saSave.Add ( "6"); saOut.Add ("Р”Р»РёРЅСѓ Р‘РѕР»СЊС€.РЎС‚РѕСЂ.");
      saSave.Add ( "7"); saOut.Add ("РЁС‚.Р±РµР· РђСЂРіРѕРЅР°"    );
      saSave.Add ( "8"); saOut.Add ("РЁС‚.СЃ РђСЂРіРѕРЅРѕРј"     );
      saSave.Add ( "9"); saOut.Add ("РџР»РѕС‰.Р±РµР· РђСЂРіРѕРЅР°"  );
      saSave.Add ("10"); saOut.Add ("РџР»РѕС‰.СЃ РђСЂРіРѕРЅРѕРј"   );
      saSave.Add ("14"); saOut.Add ("РџРµСЂРёРјРµС‚СЂ РїРѕ СЃРµРіРјРµРЅС‚Р°Рј");
      saSave.Add ("47"); saOut.Add ("РџРµСЂРёРјРµС‚СЂ РїРѕ СЃРµРіРјРµРЅС‚Р°Рј(Рљ)");     }
    CADOGridLinkField  *pWriteTo = new CADOGridLinkField ("РЎРїРёСЃР°РЅРёРµ РЅР°", "nWriteType", saOut, saSave);
    pWriteTo->SetComboBox(true);
    m_Grid.AddField (pWriteTo);
            if ( m_eWMType == e_Glass )
    {
                  CADOGridLinkFieldMaster  *pWidthType = new CADOGridLinkFieldMaster("РЁРёСЂРёРЅР°", "idWidthType", "ID", "Name");
      RecordsetOpenReadOpt(pWidthType->m_Recordset, "select ID, Name, Width from WidthType order by Width", pMF->m_Conn.GetInterfacePtr());
      if ( IsEmpty(pWidthType->m_Recordset) )
      {
        theApp.MessageBox("РЎРїСЂР°РІРѕС‡РЅРёРє РЁРёСЂРёРЅР° РЅРµ Р·Р°РїРѕР»РЅРµРЅ. РџСЂРѕРІРµСЂСЊС‚Рµ РїСЂР°РІРёР»СЊРЅРѕСЃС‚СЊ РЅР°СЃС‚СЂРѕР№РєРё.");
        return FALSE;
      }
      pWidthType->SetComboBox (true);
      pWidthType->SetEnableNULL (true, false, " ");
      pWidthType->SetFindDefaultVal (false);
      m_Grid.AddField (pWidthType);
                  CADOGridLinkFieldMaster  *pColor = new CADOGridLinkFieldMaster("Р¦РІРµС‚", "idColor", "ID", "Name");
      RecordsetOpenReadOpt(pColor->m_Recordset, "select ID, Name from Color order by Name", pMF->m_Conn.GetInterfacePtr());
      if ( IsEmpty(pColor->m_Recordset) )
      {
        theApp.MessageBox("РЎРїСЂР°РІРѕС‡РЅРёРє Р¦РІРµС‚РѕРІ РЅРµ Р·Р°РїРѕР»РЅРµРЅ. РџСЂРѕРІРµСЂСЊС‚Рµ РїСЂР°РІРёР»СЊРЅРѕСЃС‚СЊ РЅР°СЃС‚СЂРѕР№РєРё.");
        return FALSE;
      }
      pColor->SetComboBox (true);
      pColor->SetEnableNULL (true, false, " ");
      pColor->SetFindDefaultVal (false);
      m_Grid.AddField (pColor);
    }
            CADOGridLinkFieldMaster  *pMaterialName = new CADOGridLinkFieldMaster("РњР°С‚РµСЂРёР°Р»", "idMaterial", "ID", "Name");
    RecordsetOpenReadOpt(pMaterialName->m_Recordset, "select IsNull(Name, '') + ' ' + IsNull(Art,'') as Name, ID "
                                                     "from Material where Name is not NULL and nMaterType = 1", pMF->m_Conn.GetInterfacePtr());
    if ( IsEmpty(pMaterialName->m_Recordset) )
    {
      theApp.MessageBox("РЎРїСЂР°РІРѕС‡РЅРёРє РњР°С‚РµСЂРёР°Р»РѕРІ РЅРµ Р·Р°РїРѕР»РЅРµРЅ. РџСЂРѕРІРµСЂСЊС‚Рµ РїСЂР°РІРёР»СЊРЅРѕСЃС‚СЊ РЅР°СЃС‚СЂРѕР№РєРё.");
      return FALSE;
    }
    pMaterialName->SetComboBox (false);
    pMaterialName->bEditable = false;
    m_Grid.AddField (pMaterialName);         m_Grid.AddField ("+ Рє СЂР°Р·РјРµСЂСѓ", "SizeAdd" );
    m_Grid.AddField ("+ Рє СЂР°Р·Рј. X", "SizeAddX");
    m_Grid.AddField ("+ Рє СЂР°Р·Рј. Y", "SizeAddY");

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
      m_Grid.AddField ("РљРѕСЂСЂРµРєС†РёСЏ РЅРѕСЂРјС‹ +/-", "NormAdd");
    }

    CADOGridLinkField  * pNorm = new CADOGridLinkField ("РќРѕСЂРјР°", "idNorm", saOut, saSave);
    pNorm->SetComboBox(true);
    m_Grid.AddField (pNorm);

    m_Grid.AddField ("РљРѕР»-РІРѕ", "nCount");

    CADOGridLinkField  *pCondition = new CADOGridLinkField("РЈСЃР»РѕРІРёРµ", "ConditionScript");
    m_Grid.AddField(pCondition);
    pCondition->SetButton(true);
    pCondition->BnClick = fnText;

    CADOGridLinkField  *pNumber = new CADOGridLinkField("Р¤РѕСЂРјСѓР»Р° РљРѕР»-РІРѕ", "NumberScript");
    m_Grid.AddField(pNumber);
    pNumber->SetButton(true);
    pNumber->BnClick = fnText;

    CADOGridLinkField  * m_lbCriterion = new CADOGridLinkField("РљСЂРёС‚РµСЂРёРё",  "CriterionExist");
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
            CADOGridLinkField  *pSetColor    = new CADOGridLinkField("РџСЂРёСЃРІ.Р¦РІРµС‚?",     "bSetColor"   );
      pSetColor->SetCheckBox(true);
      m_Grid.AddField(pSetColor);
            CADOGridLinkField  *pSetColorIns = new CADOGridLinkField("РџСЂРёСЃРІ.Р¦РІ.Р’РЅСѓС‚СЂ?", "bSetColorIns");
      pSetColorIns->SetCheckBox(true);
      m_Grid.AddField(pSetColorIns);
            CADOGridLinkField  *pSetColorBase = new CADOGridLinkField("РџСЂРёСЃРІ.Р¦РІ.РћСЃРЅ?", "bSetColorBase");
      pSetColorBase->SetCheckBox(true);
      m_Grid.AddField(pSetColorBase);
            CADOGridLinkField  *pSetColorExt = new CADOGridLinkField("РџСЂРёСЃРІ.Р¦РІ.Р’РЅРµС€?",  "bSetColorExt");
      pSetColorExt->SetCheckBox(true);
      m_Grid.AddField(pSetColorExt);
            CADOGridLinkField  *pColorSwap = new CADOGridLinkField("РњРµРЅСЏС‚СЊ Р’РЅСѓС‚.Р¦РІ.РЅР° Р’РЅРµС€?", "bColorSwap");
      pColorSwap->SetCheckBox(true);
      m_Grid.AddField(pColorSwap);
    }         CADOGridLinkFieldMaster  *pColorGroup = new CADOGridLinkFieldMaster("Р“СЂСѓРїРїР° С†РІРµС‚РѕРІ", "idColorGroup", "ID", "Name");
    RecordsetOpenReadOpt(pColorGroup->m_Recordset, "select ID, Name from ColorGroup order by Name", pMF->m_Conn.GetInterfacePtr());

    pColorGroup->SetComboBox (true);
    pColorGroup->SetEnableNULL (true, true, " ");
    pColorGroup->SetFindDefaultVal (false);
    m_Grid.AddField (pColorGroup);

    CADOGridLinkField  *pNotExecColorGroup = new CADOGridLinkField("РћС‚СЂРёС†Р°РЅРёРµ?", "bNotExecColorGroup");
    pNotExecColorGroup->SetCheckBox (true);
    m_Grid.AddField (pNotExecColorGroup);

    m_Grid.AddField ("РЁР°Рі", "Step");

    m_Grid.AddField ("РњРёРЅ.Р·РЅР°С‡.",  "MinVal");
    m_Grid.AddField ("РњР°РєСЃ.Р·РЅР°С‡.", "MaxVal");

    m_Grid.AddField ("Р›РµРІС‹Р№ СѓРіРѕР»",  "AngleLeft" );
    m_Grid.AddField ("РџСЂР°РІС‹Р№ СѓРіРѕР»", "AngleRight");

    CADOGridLinkField  * pIsAdd = new CADOGridLinkField("Р”РѕРї.РћРїРµСЂР°С†РёСЏ", "IsAdd");
    pIsAdd->SetCheckBox (true);
    m_Grid.AddField (pIsAdd);

    if ( m_eWMType == e_Glass )
    {
            CADOGridLinkField  *pSetColorBase = new CADOGridLinkField("РџСЂРёСЃРІ.Р¦РІ.РћСЃРЅ?", "bSetColorBase");
      pSetColorBase->SetCheckBox(true);
      m_Grid.AddField(pSetColorBase);
    }
    else
    {
      CADOGridLinkFieldMaster  *pTypeMontage = new CADOGridLinkFieldMaster ("РўРёРї РјРѕРЅС‚Р°Р¶Р°", "idTypeMontage", "ID", "Name", true);
      sSQL = "select "
             "  ID, "
             "  Name + case when IsNull(bWriteToMontageProject, 0) = 1 then ' (СЃРїРёСЃ. РЅР° РјРѕРЅС‚Р°Р¶РЅС‹Рµ СЂР°Р±РѕС‚С‹)' else '' end as Name "
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
       theApp.MessageBox("РќРµ Р·Р°РґР°РЅР° СЃРёСЃС‚РµРјР° РїСЂРѕС„РёР»РµР№");
      else if ( nGPWidth == 0)
       theApp.MessageBox("РќРµ Р·Р°РґР°РЅР° С‚РѕР»С‰РёРЅР° СЃС‚РµРєР»РѕРїР°РєРµС‚Р°");
    }
    else
      theApp.MessageBox("РќРµРІРѕР·РјРѕР¶РЅРѕ РЅР°СЃС‚СЂРѕРёС‚СЊ СЃРїРёСЃР°РЅРёРµ РЅР° РїСЂРѕС„РёР»СЏ");
  }
  CATCH_SHOW(__FILE__, __LINE__, __FUNCTION__)
}

