#ifndef _INSIDE_VISUAL_CPP_IMGCENTERDIB
#define _INSIDE_VISUAL_CPP_IMGCENTERDIB


// CDib类
class AFX_EXT_CLASS CDib
{

private:

	// 图像信息头指针
	LPBITMAPINFOHEADER m_lpBmpInfoHead; 

	// 图像颜色表指针
	LPRGBQUAD m_lpColorTable; 

	// 图像数据指针
	unsigned char * m_pImgData; 

	// 指向DIB的指针（包含BITMAPINFOHEADER、颜色表和数据）
	// m_lpDib = m_lpBmpInfoHead + m_lpColorTable + m_pImgData
	LPBYTE m_lpDib;

	// 每像素占的位数
	int m_nBitCount;

	
	// 逻辑调色板句柄
	HPALETTE m_hPalette;

	// 颜色表长度（多少个表项）
	int m_nColorTableLength;


	// 图像的宽，像素为单位
	int m_imgWidth;

	// 图像的高，像素为单位
	int m_imgHeight;


public:

	CDib();

	CDib( CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
		  unsigned char *pImgData);

	~CDib();

public:

	// 获取DIB的尺寸（宽高）
	CSize GetDimensions() const;

	// DIB读函数
	BOOL Read(LPCTSTR lpszPathName);

	// DIB写函数
	BOOL Write(LPCTSTR lpszPathName);

	// 显示DIB（如果size的长或宽出现零值，则默认使用图像的大小）
	BOOL Draw(CDC* pDC, const CPoint& origin, CSize size);  

	// 用新的DIB数据更新
	// 当nBitCount=16或24时，lpColorTable可以为NULL
	BOOL AttachDIBitmap( CSize size, int nBitCount, LPRGBQUAD lpColorTable,
					 unsigned char *pImgData);

	// 用新的DDB数据更新
	// 当nBitCount=16或24时，lpColorTable可以为NULL
	BOOL AttachDDBitmap( CSize size, int nBitCount, LPRGBQUAD lpColorTable,
					     unsigned char *pImgData);

	
private:

	// 计算颜色表的长度
	int ComputeColorTabalLength(int nBitCount) const;

	// 创建逻辑调色板
	void MakePalette();

	// 清理空间
	void Empty();	
};
#endif // _INSIDE_VISUAL_CPP_IMGCENTERDIB
