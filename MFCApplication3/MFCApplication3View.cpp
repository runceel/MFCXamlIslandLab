
// MFCApplication3View.cpp : implementation of the CMFCApplication3View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCApplication3.h"
#endif

#include "MFCApplication3Doc.h"
#include "MFCApplication3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace winrt;
using namespace Windows::UI;
using namespace Windows::UI::Composition;
using namespace Windows::UI::Xaml::Hosting;


// CMFCApplication3View

IMPLEMENT_DYNCREATE(CMFCApplication3View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication3View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCApplication3View::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCApplication3View construction/destruction

CMFCApplication3View::CMFCApplication3View() noexcept
{
	// TODO: add construction code here

}

CMFCApplication3View::~CMFCApplication3View()
{
}

BOOL CMFCApplication3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

int CMFCApplication3View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	DesktopWindowXamlSource desktopSource;
	auto interop = desktopSource.as<IDesktopWindowXamlSourceNative>();
	check_hresult(interop->AttachToWindow(this->GetSafeHwnd()));

	HWND hWndXamlIsland = nullptr;
	interop->get_WindowHandle(&hWndXamlIsland);
	auto result = ::SetWindowPos(this->GetSafeHwnd(), hWndXamlIsland, 100, 100, 500, 500, SWP_SHOWWINDOW);
	if (!result)
	{
		DWORD errorcode = GetLastError();
		LPVOID lpMsgBuf;
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER
			| FORMAT_MESSAGE_FROM_SYSTEM
			| FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, errorcode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0,
			NULL);

		MessageBox((LPCTSTR)lpMsgBuf, _TEXT("Error"), MB_OK | MB_ICONINFORMATION);
		LocalFree(lpMsgBuf);
		return -1;
	}

	//Windows::UI::Xaml::Controls::TreeView treeView;
	//Windows::UI::Xaml::Controls::TreeViewNode rootNode;
	//rootNode.Content(winrt::box_value(L"Hello TreeView on MFC"));
	//auto rootNodes = treeView.RootNodes();
	//rootNodes.Append(rootNode);

	//desktopSource.Content(treeView);
	
	//Creating the Xaml content
	Windows::UI::Xaml::Controls::StackPanel xamlContainer;
	xamlContainer.Background(Windows::UI::Xaml::Media::SolidColorBrush{ Windows::UI::Colors::LightGray() });

	Windows::UI::Xaml::Controls::TextBlock tb;
	tb.Text(L"Hello World from Xaml Islands!");
	tb.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Center);
	tb.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Center);
	tb.FontSize(48);

	xamlContainer.Children().Append(tb);
	xamlContainer.UpdateLayout();
	desktopSource.Content(xamlContainer);

	return 0;
}
// CMFCApplication3View drawing

void CMFCApplication3View::OnDraw(CDC* /*pDC*/)
{
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMFCApplication3View printing


void CMFCApplication3View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCApplication3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCApplication3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCApplication3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMFCApplication3View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCApplication3View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCApplication3View diagnostics

#ifdef _DEBUG
void CMFCApplication3View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication3Doc* CMFCApplication3View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication3Doc)));
	return (CMFCApplication3Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication3View message handlers
