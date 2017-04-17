// GDI+SampleView.cpp : CGDISampleView 类的实现
//

#include "stdafx.h"
#include "GDI+Sample.h"

#include "GDI+SampleDoc.h"
#include "GDI+SampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGDISampleView

IMPLEMENT_DYNCREATE(CGDISampleView, CView)

BEGIN_MESSAGE_MAP(CGDISampleView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_DRAWLINE, &CGDISampleView::OnDrawline)
	ON_COMMAND(ID_RECTANGLE, &CGDISampleView::OnRectangle)
	ON_COMMAND(ID_DRAWSTRING, &CGDISampleView::OnDrawstring)
	ON_COMMAND(ID_EFFECTFONT, &CGDISampleView::OnShadowfont)
	ON_COMMAND(ID_SURROUNDED, &CGDISampleView::OnBubbleSurround)
	ON_COMMAND(ID_EMBOSS, &CGDISampleView::OnEmboss)
    ON_COMMAND(ID_OUTLINE, &CGDISampleView::OnOutline)
    ON_COMMAND(ID_WARPED, &CGDISampleView::OnWarped)
    ON_COMMAND(ID_BLOCK, &CGDISampleView::OnBlock)
    ON_COMMAND(ID_OUTGLOWING, &CGDISampleView::OnOutglowing)
    ON_WM_CONTEXTMENU()
    ON_COMMAND(ID_CLIPPATH, &CGDISampleView::OnClippath)
    ON_COMMAND(ID_DRAWIMAGE, &CGDISampleView::OnDrawimage)
END_MESSAGE_MAP()

// CGDISampleView 构造/析构

CGDISampleView::CGDISampleView()
{
	// TODO: 在此处添加构造代码

}

CGDISampleView::~CGDISampleView()
{
}

BOOL CGDISampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}



// CGDISampleView 打印

BOOL CGDISampleView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // 默认准备
    return DoPreparePrinting(pInfo);
}

void CGDISampleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: 添加额外的打印前进行的初始化过程
}

void CGDISampleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: 添加打印后进行的清除过程
}


// CGDISampleView 诊断

#ifdef _DEBUG
void CGDISampleView::AssertValid() const
{
    CView::AssertValid();
}

void CGDISampleView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CGDISampleDoc* CGDISampleView::GetDocument() const // 非调试版本是内联的
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDISampleDoc)));
    return (CGDISampleDoc*)m_pDocument;
}
#endif //_DEBUG

void CGDISampleView::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
    CMenu popMenu;
    popMenu.LoadMenu(IDR_MAINFRAME);
    CMenu* pMenu = popMenu.GetSubMenu(4);
    // 弹出菜单
    pMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,point.x,point.y,this);
}

// CGDISampleView 绘制

void CGDISampleView::OnDraw(CDC* pDC)
{
	CGDISampleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)        return;

    //////////////////////////////////////////////////////////////////////////
    OnDrawimage();


    

}
// CGDISampleView 消息处理程序

void CGDISampleView::OnDrawline()
{
	CClientDC dc(this);
    Graphics g(dc.m_hDC);
    g.SetSmoothingMode(SmoothingModeAntiAlias);

#if 0
	// Pen can also be constructed using a brush or another pen.  
	// There is a second parameter - a width which defaults to 1.0f
	Pen	blue (Color(255, 0, 0, 255));
	Pen red  (Color(255, 255, 0, 0));

	int y = 256;
	int x = 0;
	for (x = 0; x < 256; x += 5)
	{
		g.DrawLine(&blue, 0, y, x, 0);
		g.DrawLine(&red, 256, x, y, 256);  
		y -= 5;
	}

	for (y = 0; y < 256; y++)
	{
		Pen pen(Color(y, 0, 255,0));  // A green pen with shifting alpha
		g.DrawLine(&pen, 0, y, 256, y);
		// The sleep is to slow it down so you can watch the effect
		//Sleep(20);
	}

	for (x = 0; x < 256; x++)
	{
		Pen pen(Color(x, 255, 0, 255));  // A green pen with shifting alpha
		g.DrawLine(&pen, x, 100, x, 200);
		// The sleep is to slow it down so you can watch the effect
		//Sleep(20);
	}
#endif

    // Draw curve
    Point ptCurve[] = { Point(300,300),Point(400,400),Point(500,350)};

    Pen penCurve(Color::Blue,2);
    g.DrawCurve(&penCurve,ptCurve,3,0);

    Pen penCurve1(Color::Yellow,2);
    g.DrawCurve(&penCurve1,ptCurve,3,1);
    
    Pen penCurve2(Color::Red,2);
    g.DrawCurve(&penCurve2,ptCurve,3,2);

    Pen penCurve3(Color::Green,2);
    g.DrawCurve(&penCurve3,ptCurve,3,0.5);

    g.DrawClosedCurve(&Pen(Color::SkyBlue,1),ptCurve,3,1.5);
    //g.FillClosedCurve(&SolidBrush(Color::Gray),ptCurve,3,FillMode::FillModeWinding,0);
    


    //////////////////////////////////////////////////////////////////////////
    Rect rect(0, 0, 50, 50);
   
    g.DrawRectangle(&penCurve, rect);
    
    g.ResetTransform();

    g.RotateTransform(30);
    g.DrawRectangle(&penCurve2, rect);

    g.ScaleTransform(1.75f, 0.5f, MatrixOrderAppend); 
    g.DrawRectangle(&penCurve1, rect);

    g.TranslateTransform(150, 50, MatrixOrderAppend);
    g.DrawRectangle(&penCurve2, rect);

    //////////////////////////////////////////////////////////////////////////
    g.ResetTransform();
    Matrix matrix(0.866*1.75,0.5*0.5,-0.5*1.75,0.866*0.5,150,50);
    g.SetTransform(&matrix);
    g.DrawRectangle(&Pen(Color::Blue,1), rect);


}

void CGDISampleView::OnRectangle()
{
	CClientDC dc(this);
	Graphics graphics(dc.m_hDC);


	GraphicsPath path; // 构造一个路径
	path.AddEllipse(50, 50, 200, 100);

	// 使用路径构造一个画刷
	PathGradientBrush pthGrBrush(&path);

	// 将路径中心颜色设为蓝色
	pthGrBrush.SetCenterColor(Color(255, 0, 0, 255));

	// 设置路径周围的颜色为蓝芭，但alpha值为0
	Color colors[] = {Color(0, 0, 0, 255)};
	INT count = 1;
	pthGrBrush.SetSurroundColors(colors, &count);

	graphics.FillRectangle(&pthGrBrush, 50, 50, 200, 100);

}

void CGDISampleView::OnDrawstring()
{
	CClientDC dc(this);
    Graphics g(dc.m_hDC);

    CString strText = _T("北京软通动力信息技术有限公司");

    StringFormat strFmt;//(StringFormat::GenericDefault());
//     strFmt.SetFormatFlags( StringFormatFlagsDirectionRightToLeft |
//     StringFormatFlagsDirectionVertical | 
//         StringFormatFlagsNoFitBlackBox|StringFormatFlagsNoClip);
    //INT formatflags = strFmt.GetFormatFlags();

    strFmt.SetAlignment(StringAlignmentCenter);
    strFmt.SetLineAlignment(StringAlignmentCenter);

	// a linear gradient brush
	LinearGradientBrush linGrBrush(
		Point(300, 50),
		Point(500, 150),
		Color(255, 255, 255, 0), // yellow
		Color(255, 0, 0, 255)); // 蓝色

    Font font(_T("楷体_GB2312"),20);
    /*FontFamily fFamily;
    font.GetFamily(&fFamily);*/

    RectF txtRect;
    g.MeasureString(strText,strText.GetLength(),&font,PointF(0,0),&strFmt,&txtRect);
    txtRect.X = 0;
    txtRect.Y = 0;
    g.FillRectangle(&linGrBrush,txtRect);



	//
    //strText = _T("北京");
    g.DrawString(strText,strText.GetLength(), &font,txtRect,&strFmt,&SolidBrush(Color(50,0,0,0)));

}


// effect font
// 1.为了取得阴影效果，你只需要绘制文本两次。
//   首先是阴影文本然后是最前面的文本。例如，下面的代码绘制了一个阴影文本，阴影文本在前端文本后方5个像素处


void CGDISampleView::OnShadowfont()
{
	CClientDC dc(this);
	Graphics g(dc.m_hDC);
    g.Clear(Color(255,255,255));

	// a hatch brush
	//HatchBrush hatchBrush(HatchStyleSmallGrid,
	//	Color(255,0,0),Color(0,0,255));

	//// a linear gradient brush
	//LinearGradientBrush linGrBrush(
	//	Point(300, 50),
	//	Point(500, 150),
	//	Color(150, 255, 0, 0), // 红色
	//	Color(150, 0, 0, 255)); // 蓝色


	//
	PointF ptStart(100,100);
	Font fontNormal(_T("PL 07 Sans"), 8);


    // Draw a shadow text
    CString strShadow = _T("阴影字\n a bTest");

    g.DrawString(strShadow,strShadow.GetLength(), &fontNormal, PointF(30,20),&SolidBrush(Color(0,0,0)));
    //g.DrawString(strShadow,strShadow.GetLength(), &fontNormal, PointF(0,0),&SolidBrush(Color(200,10,10)));
    
}


// 轮廓线
void CGDISampleView::OnOutline()
{
    CClientDC dc(this);
    Graphics g(dc.m_hDC);
    g.Clear(Color::White);
    g.SetSmoothingMode(SmoothingModeAntiAlias);

    CString strText = _T("Test");


    StringFormat strFmt(StringFormat::GenericTypographic());
    //strFmt.SetFormatFlags( StringFormatFlagsDirectionLeftToRight); 

    //strFmt.SetAlignment(StringAlignment::StringAlignmentCenter);
    //strFmt.SetLineAlignment(StringAlignmentCenter);
    

    Font font(_T("Arial"),60,FontStyleBold,UnitPixel,&InstalledFontCollection());
    FontFamily fFamily;
    font.GetFamily(&fFamily);

    /*RectF txtRect;
    g.MeasureString(strText,strText.GetLength(),&font,PointF(0,0),&strFmt,&txtRect);
    g.FillRectangle(&SolidBrush(Color(0,0,0)),txtRect);*/

    // create a path 
    GraphicsPath path; 
    path.AddString( strText,strText.GetLength(),
        &fFamily,font.GetStyle(),font.GetSize(),
        PointF(0,0), &strFmt);

    // Select the pen
    //Matrix matrix;
    //matrix.Scale(1.1,1.1);
    //matrix.Translate(-3,-3);
    /*matrix.Translate(0,2);
    matrix.Translate(-2,0);
    matrix.Translate(0,-2);*/
    //path.Transform(&matrix);


    //Pen pen(Color::Blue,2.0);

    // Fill it 
    g.FillPath( &SolidBrush(Color(0,0,255)),&path); 

    // outline it 
    //g.DrawPath(&Pen(Color::Red,3.0),&pth);

    //
    g.DrawString(strText,strText.GetLength(),&font,PointF(0,0),&strFmt,&SolidBrush(Color(0,0,0)));



}



// 环绕文本
void CGDISampleView::OnBubbleSurround()
{
	CClientDC dc(this);
	Graphics graphics(dc.m_hDC);

	// a linear gradient brush
	LinearGradientBrush linGrBrush(
		Point(300, 50),
		Point(500, 150),
		Color(150, 255, 0, 0), // 红色
		Color(150, 0, 0, 255)); // 蓝色


	// a solid brush
	SolidBrush solidBrush(Color(200,0,0));


	//
	PointF ptStart(200,200);
	//Font fontNormal(_T("PL Sans 07"), 60, FontStyleBold);
    Font fontBold(_T("Arial"), 16,FontStyleRegular);
    //Font fontThin(_T("Arial"), 16,FontStyleRegular);
	CString strText = _T("Tonite");
    //strText = _T("ABCDEFGHIJ");


    RectF layoutRect;
    graphics.MeasureString(strText,strText.GetLength(),&fontBold,ptStart,&layoutRect);
    graphics.FillRectangle(&SolidBrush(Color.LightBlue),layoutRect);
   


	int iWidth = 4;

	int i=0;

	//////////////////////////////////////////////////////////////////////////
    // 左移、右移、上移、下移
	for (i=0; i<iWidth; i++)
	{
		graphics.DrawString(strText,strText.GetLength(), &fontBold, 
			PointF(ptStart.X-i,ptStart.Y),&solidBrush);
	}

	for (i=0; i<iWidth; i++)
	{
		graphics.DrawString(strText,strText.GetLength(), &fontBold, 
			PointF(ptStart.X+i,ptStart.Y),&solidBrush);
	}

	for (i=0; i<iWidth; i++)
	{
		graphics.DrawString(strText,strText.GetLength(), &fontBold, 
			PointF(ptStart.X,ptStart.Y+i),&solidBrush);
	}

	for (i=0; i<iWidth; i++)
	{
		graphics.DrawString(strText,strText.GetLength(), &fontBold, 
			PointF(ptStart.X,ptStart.Y-i), &solidBrush);
	}

	//////////////////////////////////////////////////////////////////////////
	for (i=0; i<iWidth; i++)
	{
		graphics.DrawString(strText,strText.GetLength(), &fontBold, 
			PointF(ptStart.X-i,ptStart.Y-i), &solidBrush);
	}

	for (i=0; i<iWidth; i++)
	{
		graphics.DrawString(strText,strText.GetLength(), &fontBold, 
			PointF(ptStart.X+i,ptStart.Y-i),&solidBrush);
	}

	for (i=0; i<iWidth; i++)
	{
		graphics.DrawString(strText,strText.GetLength(), &fontBold, 
			PointF(ptStart.X+i,ptStart.Y+i),&solidBrush);
	}

	for (i=0; i<iWidth; i++)
	{
		graphics.DrawString(strText,strText.GetLength(), &fontBold, 
			PointF(ptStart.X-i,ptStart.Y+i), &solidBrush);
	}

	// surrounded
	graphics.DrawString(strText,strText.GetLength(), &fontBold, ptStart, &SolidBrush(Color(0,255,255)));
}

// 浮雕效果常常通过阴影文本技术来实现，深度设置为1个像素，前景文本的颜色设置为背景颜色。
// 阴影的文本的颜色选择黑色或灰色。
// 雕刻效果的步骤相反，阴影文本相对于前面的文本向左上方偏移一个像素。 

// 浮雕文本
// 雕刻文本
void CGDISampleView::OnEmboss()
{
	CClientDC dc(this);
	Graphics graphics(dc.m_hDC);
	graphics.Clear(Color(255,255,255));


	// a solid brush
	SolidBrush blackBursh(Color(0,0,0));
	SolidBrush witheBursh(Color(255,255,255));


	//
	PointF ptStart1(200,200);
	Font fontNormal(_T("Times new Roman"), 60, FontStyleBold);

    //
	CString strText = _T("浮雕文本");
	graphics.DrawString(strText,strText.GetLength(), &fontNormal, ptStart1,&blackBursh);
	graphics.DrawString(strText,strText.GetLength(), &fontNormal, PointF(ptStart1.X+1,ptStart1.Y+1),&witheBursh);

    //
    PointF ptStart2(200,10);
    strText = _T("雕刻文本");
    graphics.DrawString(strText,strText.GetLength(), &fontNormal, ptStart2,&blackBursh);
    graphics.DrawString(strText,strText.GetLength(), &fontNormal, PointF(ptStart2.X-1,ptStart2.Y-1),&witheBursh);
}

// 歪曲文字
void CGDISampleView::OnWarped()
{

    CClientDC dc(this);
    Graphics graphics(dc.m_hDC);
    graphics.Clear(Color(0,0,0));

    //create a path 

    GraphicsPath pth; 

    CString strText = _T("The Star Wars III"); 

    FontFamily ff(_T("Verdana")); 

    //Add the text strings 
    for(int y=0;y<5;y++) 
    { 
        pth.AddString(strText,strText.GetLength(),
            &ff,0,70, Point(0,90*y), StringFormat::GenericTypographic()); 
    } 

    //Create the warp array 
    CRect rect;
    GetClientRect(&rect);

    PointF points[] = { 
            PointF(rect.Width()/2-rect.Width()/4,0), 
            PointF(rect.Width()/2+rect.Width()/4,0), 
            PointF(0,rect.Height()), 
            PointF(rect.Width(),rect.Height()) 
    }; 

    //Warp the path 
    pth.Warp(points,4,RectF(0,0,820,450)); 

    //Fill the background 
    graphics.Clear(Color(0,0,0));
    //graphics.FillRectangle(&SolidBrush(Color::Black),RectF()); 

    //Paint the warped path by filling it 
    graphics.FillPath(&SolidBrush(Color::Yellow),&pth);

}

//////////////////////////////////////////////////////////////////////////
// *.为了实现块状文本效果，从希望的背景出开始一个像素一个像素地移动位置，并绘制文本。
//   非常明显，这时需要确定重复绘制文本的方向。
//   示例程序绘制文本时将光源设置在右上角，这意味着要使用for循环，并在X方面上减少偏移量。
//   如果将光源移动到左上角，只需要反过来增加偏移量就可以了。
void CGDISampleView::OnBlock()
{

    CClientDC dc(this);
    Graphics graphics(dc.m_hDC);
    graphics.Clear(Color(0,0,0));


    // a solid brush
    SolidBrush solidBrush(Color(200,50,50));

    //
    CString strText = _T("块状字\n\nTest");


    PointF ptStart(100,100);
    Font fontNormal(_T("Arial"), 60, FontStyleBold);

    for (int ii = 0; ii<10; ii ++)
    {
        ptStart.X -= 1;
        //ptStart.Y += 1;

        graphics.DrawString(
            strText,strText.GetLength(), 
            &fontNormal, 
            ptStart,
            &SolidBrush(Color(255,255,255)));
    }

    //
    graphics.DrawString(strText,strText.GetLength(), &fontNormal, ptStart,&solidBrush); 

}

//////////////////////////////////////////////////////////////////////////
/*
你可能会认为生成一个带柔和阴影的特效文字与生成一个带光圈的特效文字是完全不同的，
其实他们所用到的技术是完全相同的，只是在设置上有些许变化。
在带柔和阴影的效果中，我用到了GDI+中的一些插值模式来生成模糊的文字轮廓，当位图绘制平面放大时，
插值模式决定原来某点像素应该怎样和周围的融合。低质量的插值只是简单的把一个像素变换成同色色块，
高质量插值如高质量双线性插值与高质量双三次插值会考虑像素色的平滑与反走样，我发现高质量双线性
插值模式最好。

这个技术把文字绘制两次，一次在一个小位图上绘制光圈，它将被用你所选的插值模式放大，另一次将在
平面上绘制实际文字。用于生成光圈的位图必须与实际文字成比例，在这儿我用1/5，因此光圈文字大小
是实际文字的1/5。


步骤如下：

建一个比实际绘制区域小的成比例的位图，这儿我用1/5；
建一个路径，把你想要生成效果的文字加入路径中；
用1中位图创建Graphics，建一个能缩小输出图形的矩阵；
用你想要的光圈颜色，填充文本路径，为了调节，用很细的画笔描出路径；
设置你要输出位图的Graphics的插值模式为高质双线形性，把光圈位图按比例放大到目标Graphic上；
最后，在目标Graphic上，按实际尺寸填充文本路径，这样将生成下面所示光圈效果；

*/
// 光圈文字
void CGDISampleView::OnOutglowing()
{

    CClientDC dc(this);
    Graphics g(dc.m_hDC);
    g.Clear(Color(0,0,0));

    int iFontHeight = 24;
    int iSizeCircle = iFontHeight/4;

    //客户区大小
    CRect ClientRect;
    GetClientRect(&ClientRect);
    CSize ClientSize(ClientRect.Width(),ClientRect.Height());
    
    RectF ClientRectangle(ClientRect.top,ClientRect.left,ClientRect.Width(),ClientRect.Height()); 
    g.FillRectangle(&SolidBrush(Color::White),ClientRectangle);
    Bitmap bm(ClientSize.cx/iSizeCircle,ClientSize.cy/iSizeCircle,&g);

    //创建文字路径 
    GraphicsPath pth;
    //Add the string in the chosen style. 
    int style = FontStyleRegular;
    pth.AddString(_T("Tonite"),-1,&FontFamily(_T("Arial")),style,iFontHeight,Point(20,20),NULL);

    //位图Graphics
    Graphics* bmpG = Graphics::FromImage(&bm);
    //Create a matrix that shrinks the drawing output by the fixed ratio. 
    Matrix mx(1.0f/iSizeCircle,0,0,1.0f/iSizeCircle,-(1.0f/iSizeCircle),-(1.0f/iSizeCircle));
    //Choose an appropriate smoothing mode for the halo. 
    bmpG->SetSmoothingMode(SmoothingModeAntiAlias);

    //Transform the graphics object so that the same half may be used for both halo and text output. 

    //变换为位图的1/5，放大后将和实际文本相仿
    bmpG->SetTransform(&mx);
    
    //Using a suitable pen...
    Pen p(Color::Blue,3);
    
    //Draw around the outline of the path
    bmpG->DrawPath(&p,&pth);
    
    //and then fill in for good measure. 
    bmpG->FillPath(&SolidBrush(Color::Blue),&pth);
    
    //this just shifts the effect a little bit so that the edge isn''t cut off in the demonstration 
    
    //移动50，50
    g.SetTransform(&Matrix(1,0,0,1,50,50));
    
    //setup the smoothing mode for path drawing
    g.SetSmoothingMode(SmoothingModeAntiAlias);
    
    //and the interpolation mode for the expansion of the halo bitmap 
    g.SetInterpolationMode(InterpolationModeHighQualityBicubic);
    
    //expand the halo making the edges nice and fuzzy. 
    g.DrawImage(&bm,ClientRectangle,0,0,bm.GetWidth(),bm.GetHeight(),UnitPixel);
    
    //Redraw the original text 
    g.FillPath(&SolidBrush(Color::Black),&pth);
}

#include <math.h>
void CGDISampleView::OnClippath()
{
    HDC hdc = ::GetDC(this->GetSafeHwnd()); 
    SIZE sz;                // structure that receives text extents 

    RECT rc;                // structure for painting window 
    GetClientRect(&rc); 
    ::FillRect(hdc, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH)); 

    // Retrieve a cached DC for the window. 


    // Use the font requested by the user in the 
    // Choose Font dialog box to create a logical
    // font, then select that font into the DC. 
    // Describe a 24-point truetype font of normal weight
    LOGFONT lf;
    memset(&lf, 0, sizeof(lf));
    lf.lfHeight = -MulDiv(40, GetDeviceCaps(hdc,LOGPIXELSY), 72);
    lf.lfWeight = FW_NORMAL;
    lf.lfOutPrecision = OUT_TT_ONLY_PRECIS;

    HFONT hfont = CreateFontIndirect(&lf); 
    HFONT hfontOld = (HFONT)::SelectObject(hdc, hfont); 

    // Retrieve the dimensions of the rectangle 
    // that surrounds the text. 

    ::GetTextExtentPoint32(hdc, _T("Clip Path"), 9, &sz); 

    // Set a clipping region using the rect that 
    // surrounds the text. 
    int nXStart, nYStart;   // drawing coordinates 
    nYStart = 50;
    nXStart = 50;


    HRGN hrgn = CreateRectRgn(nXStart, nYStart, 
        nXStart + sz.cx, 
        nYStart + sz.cy); 

    SelectClipRgn(hdc, hrgn); 

    // Create a clip path using text drawn with 
    // the user's requested font. 
    int iMode = RGN_COPY;
    BeginPath(hdc); 
    TextOut(hdc, nXStart, nYStart, _T("Clip Path"), 9); 
    EndPath(hdc); 
    SelectClipPath(hdc, iMode); 

    // Compute the sine of 0, 1, ... 90 degrees.
    double aflSin[90];      // sine of 0-90 degrees 
    double aflCos[90];      // cosine of 0-90 degrees 
    double flRadius;      // radius of circle 

    for (int i = 0; i < 90; i++) 
    { 
        aflSin[i] = sin( (((double)i) / 180.0) 
            * 3.14159); 
    } 

    // Compute the cosine of 0, 1,... 90 degrees. 
    for (int i = 0; i < 90; i++) 
    { 
        aflCos[i] = cos( (((double)i) / 180.0) 
            * 3.14159); 
    } 

    // Set the radius value. 

    flRadius = (double)(2 * sz.cx); 

    // Draw the 90 rays extending from the 
    // radius to the edge of the circle. 

    for (int i = 0; i < 90; i++) 
    { 
        MoveToEx(hdc, nXStart, nYStart, 
            (LPPOINT) NULL); 
        LineTo(hdc, nXStart + ((int) (flRadius 
            * aflCos[i])), 
            nYStart + ((int) (flRadius 
            * aflSin[i]))); 
    } 

    // Reselect the original font into the DC. 

    SelectObject(hdc, hfontOld); 

    // Delete the user's font. 

    DeleteObject(hfont); 

    // Release the DC. 

    ::ReleaseDC(this->GetSafeHwnd(), hdc); 

}

void CGDISampleView::OnDrawimage()
{
    CClientDC dc(this);
    //Graphics g(dc.m_hDC);
    //g.Clear(Color(0,0,0));


    // 客户区大小
    CRect ClientRect;
    GetClientRect(&ClientRect);
    CSize ClientSize(ClientRect.Width(),ClientRect.Height());

#if 0
    //////////////////////////////////////////////////////////////////////////
    ColorMatrix cm = {
        1,    1,      0,      0.0, 0.0 ,
        0,    0,      0,      0.0, 0.0 ,
        0,    0,      0,      0.0, 0.0 ,
        0,    0,      0.0,    1.0, 0.0 ,
        0,    0,      0.0,    0.0, 1.0 
    };

    Bitmap img(_T("mouse.bmp"));
    ImageAttributes ia;
    ia.SetColorMatrix(&cm);

//     g.DrawImage( &img, Rect(0,0,img.GetWidth(),img.GetHeight()),0,0,
//         img.GetWidth(),img.GetHeight(),
//         UnitPixel,&ia);
    RectF destRect( PointF(0,0), SizeF(ClientSize.cx,ClientSize.cy));
    g.SetInterpolationMode(InterpolationMode::InterpolationModeNearestNeighbor);
    g.DrawImage(&img,destRect,0,0,img.GetWidth(),img.GetHeight(),Unit::UnitPixel);
#endif

    CBitmap bmpTower;
    BOOL bFlag = bmpTower.LoadBitmap(IDB_TOWER);
    if (!bFlag)
    {
        return;
    }

    //
    BITMAP bmpInfo;
    bmpTower.GetBitmap(&bmpInfo);

    // load source bitmap
    CDC dcSrc;
    dcSrc.CreateCompatibleDC(NULL);
    dcSrc.SelectObject(bmpTower);


    // zoom out
    int iSmallWidth = bmpInfo.bmWidth/4;
    int iSmallHeight = bmpInfo.bmHeight/4;
    CDC dcSwap;
    dcSwap.CreateCompatibleDC(NULL);
    CBitmap bmpSwap;
    bmpSwap.CreateCompatibleBitmap(&dc,iSmallWidth,iSmallHeight);
    CBitmap* pOldSwapBmp = dcSwap.SelectObject(&bmpSwap);
    
    ::SetStretchBltMode(dcSwap,STRETCH_HALFTONE);
    ::SetBrushOrgEx(dcSwap,0,0,NULL);
    bFlag = ::StretchBlt(dcSwap,0,0,iSmallWidth,iSmallHeight,
        dcSrc,0,0,bmpInfo.bmWidth,bmpInfo.bmHeight,SRCCOPY);

    // 输出缩小的图像
    //::SetStretchBltMode(dc,HALFTONE);
    bFlag = ::StretchBlt(dc,0,0,iSmallWidth,iSmallHeight,
        dcSwap,0,0,iSmallWidth,iSmallHeight,SRCCOPY);


    // 输出经过缩小又经过放大的图像
    //::SetStretchBltMode(dc,HALFTONE);
    bFlag = ::StretchBlt(dc,100,100,bmpInfo.bmWidth,bmpInfo.bmHeight,
        dcSwap,0,0,iSmallWidth,iSmallHeight,SRCCOPY);
    //
    dcSwap.SelectObject(pOldSwapBmp);

}
