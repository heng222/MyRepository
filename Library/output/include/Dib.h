#ifndef _INSIDE_VISUAL_CPP_IMGCENTERDIB
#define _INSIDE_VISUAL_CPP_IMGCENTERDIB


// CDib��
class AFX_EXT_CLASS CDib
{

private:

	// ͼ����Ϣͷָ��
	LPBITMAPINFOHEADER m_lpBmpInfoHead; 

	// ͼ����ɫ��ָ��
	LPRGBQUAD m_lpColorTable; 

	// ͼ������ָ��
	unsigned char * m_pImgData; 

	// ָ��DIB��ָ�루����BITMAPINFOHEADER����ɫ������ݣ�
	// m_lpDib = m_lpBmpInfoHead + m_lpColorTable + m_pImgData
	LPBYTE m_lpDib;

	// ÿ����ռ��λ��
	int m_nBitCount;

	
	// �߼���ɫ����
	HPALETTE m_hPalette;

	// ��ɫ���ȣ����ٸ����
	int m_nColorTableLength;


	// ͼ��Ŀ�����Ϊ��λ
	int m_imgWidth;

	// ͼ��ĸߣ�����Ϊ��λ
	int m_imgHeight;


public:

	CDib();

	CDib( CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
		  unsigned char *pImgData);

	~CDib();

public:

	// ��ȡDIB�ĳߴ磨��ߣ�
	CSize GetDimensions() const;

	// DIB������
	BOOL Read(LPCTSTR lpszPathName);

	// DIBд����
	BOOL Write(LPCTSTR lpszPathName);

	// ��ʾDIB�����size�ĳ���������ֵ����Ĭ��ʹ��ͼ��Ĵ�С��
	BOOL Draw(CDC* pDC, const CPoint& origin, CSize size);  

	// ���µ�DIB���ݸ���
	// ��nBitCount=16��24ʱ��lpColorTable����ΪNULL
	BOOL AttachDIBitmap( CSize size, int nBitCount, LPRGBQUAD lpColorTable,
					 unsigned char *pImgData);

	// ���µ�DDB���ݸ���
	// ��nBitCount=16��24ʱ��lpColorTable����ΪNULL
	BOOL AttachDDBitmap( CSize size, int nBitCount, LPRGBQUAD lpColorTable,
					     unsigned char *pImgData);

	
private:

	// ������ɫ��ĳ���
	int ComputeColorTabalLength(int nBitCount) const;

	// �����߼���ɫ��
	void MakePalette();

	// ����ռ�
	void Empty();	
};
#endif // _INSIDE_VISUAL_CPP_IMGCENTERDIB
