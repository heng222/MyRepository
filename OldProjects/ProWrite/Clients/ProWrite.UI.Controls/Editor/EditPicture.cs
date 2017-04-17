using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using ProWrite.UI.Controls.Common;
using ProWrite.Core;
using ProWrite.Entity.Shape;
using System.Collections;
using System.Drawing.Drawing2D;
using System.IO;

namespace ProWrite.UI.Controls.Editor
{
    public partial class EditPicture : XtraForm
    {

        public enum ImageType
        {
            Empty,
            Point,
            Line,
            Rectangle,
            FillRectangle,
            Circle,
            FillCircle,
            Ellipse,
            FillEllipse,
            Path,
            Eraser,
            Text,
            CircleAt,
            Polygon,
            Curve,
            ClosedCurve,
            Beziers,
            Set,
            Pick
        }

        public Image CurrentImage
        {
            get;
            set;
        }

        public Image CurrentEditPic
        { get; set; }

        public string ImageUrl
        { get; set; }

        public ShapeImage CurrentShapeImage
        { get; set; }


        private Image CurrentImageOld;
        ImageHandler imageHandler = new ImageHandler();
        public delegate void EditShapImage(Image img);
        public event EditShapImage UpdateShapeImage;
        double zoomFactor = 1.0;
        private bool _selecting;
        private Rectangle _selection;

        DShapeList drawingList = new DShapeList();							//图元
        DShapeList drawingListUndo = new DShapeList();						//Undo保存
        DShapeList tempPoint = new DShapeList();							//多边形、曲线临时顶点
        DShapeList pointViewList = new DShapeList();						//图元顶点框
        DShapeList notchangeList = new DShapeList();						//不移图元
        DShapeList notchangeListUndo = new DShapeList();

        //NewForm newForm = new NewForm();									//字体、线宽窗口
        //CircleForm newCircle = new CircleForm();							//顶点圆窗口

        ArrayList pointCollection = new ArrayList();						//多边形、曲线顶点集合

        NewRegion regionCollection = new NewRegion();						//图元区域集合
        NewRegion regionCollectionUndo = new NewRegion();
        PointArrayCollection pointArray = new PointArrayCollection();		//图元顶点数组集合
        PointArrayCollection pointArrayUndo = new PointArrayCollection();
        TypeI drawImageType = new TypeI();									//图元形状
        TypeI drawImageTypeUndo = new TypeI();

        NewRegionArray regionArrayCollection = new NewRegionArray();		//图元顶点区域集合
        NewRegionArray regionArrayCollectionUndo = new NewRegionArray();

        GraphicsPath regionPath;											//线、多边形区域路径		

        Point[] tempPointArray;												//图元顶点临时保存
        Region[] tempRegion;												//图元顶点区域临时数组
        Point[] tempMovePoint;												//拾取起始点保存

        int regionIndex = 0;												//拾取集合索引
        int pointIndex;														//拾取顶点索引
        int Distance;														//圆半径（临时）
        int diameter;														//圆直径（临时）

        bool picked = false;												//拾取与否
        bool changed = false;												//图元变换
        bool mouseMove = false;												//拾取是否移动
        bool eraser = false;

        //零时变量，常量
        private MousePoint newPoint;
        private MousePoint tempChangePoint;
        private ImageType newType;
        private GraphicsPath mousePath;

        private string fileName = "NewFile";
        private Color newColor = Color.Red;
        private float lineWidth = 2;
        public EditPicture(ShapeImage shapeImage)//Image shape,string imageUrl)
        {
            InitializeComponent();
            CurrentShapeImage = shapeImage;
            CurrentImage = shapeImage.Image;
            CurrentImageOld = (Image)CurrentImage.Clone();
            ImageUrl = shapeImage.ImageUrl;
            InitImage();

        }

        private void InitImage()
        {

            // (Bitmap)Bitmap.FromFile("E:\\4.jpg");
            this.xtraTabControl1.SelectedTabPageIndex = 0;
            imageHandler.CurrentBitmap = (Bitmap)CurrentImage;
            imageHandler.BitmapPath = ImageUrl;
            PictureBoxImage();
            //this.AutoScroll = true;
            //this.AutoScrollMinSize = new Size(Convert.ToInt32(imageHandler.CurrentBitmap.Width * zoomFactor), Convert.ToInt32(imageHandler.CurrentBitmap.Height * zoomFactor));
        }

        private void PictureBoxImage()
        {

            //if (pictureBox1.Image != null && pictureBox1.Image != value)
            //    pictureBox1.Image.Dispose();
            //pictureBox1.Width = CurrentImage.Width;
            //pictureBox1.Height = CurrentImage.Height;
            pictureBox1.Image = imageHandler.CurrentBitmap;
            this.pictureBox1.Invalidate();

        }

        private void btnFlipVertical_Click(object sender, EventArgs e)
        {
            imageHandler.RotateFlip(RotateFlipType.RotateNoneFlipY);
            PictureBoxImage();
            //this.AutoScroll = true;
            //this.AutoScrollMinSize = new Size(Convert.ToInt32(imageHandler.CurrentBitmap.Width * zoomFactor), Convert.ToInt32(imageHandler.CurrentBitmap.Height * zoomFactor));
            //pictureBox1.Image = imageHandler.CurrentBitmap;

        }

        private void btnHorizontal_Click(object sender, EventArgs e)
        {
            imageHandler.RotateFlip(RotateFlipType.RotateNoneFlipX);
            PictureBoxImage();
            //pictureBox1.Image = imageHandler.CurrentBitmap;
            //this.AutoScroll = true;
            //this.AutoScrollMinSize = new Size(Convert.ToInt32(imageHandler.CurrentBitmap.Width * zoomFactor), Convert.ToInt32(imageHandler.CurrentBitmap.Height * zoomFactor));

        }

        private void btnRotatRight_Click(object sender, EventArgs e)
        {
            imageHandler.RotateFlip(RotateFlipType.Rotate90FlipNone);
            PictureBoxImage();
            //pictureBox1.Image = imageHandler.CurrentBitmap;
            //this.AutoScroll = true;
            //this.AutoScrollMinSize = new Size(Convert.ToInt32(imageHandler.CurrentBitmap.Width * zoomFactor), Convert.ToInt32(imageHandler.CurrentBitmap.Height * zoomFactor));
            this.pictureBox1.Invalidate();
        }

        private void btnRotateLeft_Click(object sender, EventArgs e)
        {
            imageHandler.RotateFlip(RotateFlipType.Rotate270FlipNone);
            PictureBoxImage();
            //this.AutoScroll = true;
            //this.AutoScrollMinSize = new Size(Convert.ToInt32(imageHandler.CurrentBitmap.Width * zoomFactor), Convert.ToInt32(imageHandler.CurrentBitmap.Height * zoomFactor));

        }

        private void trackBarControl1_EditValueChanged(object sender, EventArgs e)
        {
            spinEdit1.Value = tbarBrightness.Value;

        }

        private void spinEdit1_ValueChanged(object sender, EventArgs e)
        {
            tbarBrightness.Value = Convert.ToInt32(spinEdit1.Value);
            //imageHandler.CurrentBitmap = (Bitmap)CurrentEditPic.Clone();
            imageHandler.RestorePrevious();
            imageHandler.SetBrightness(tbarBrightness.Value);
            PictureBoxImage();

        }

        private void btnApply_Click(object sender, EventArgs e)
        {
            //EditPictureConfirm confirm = new EditPictureConfirm();
            //confirm.ShowModalDialog();
            //if (confirm.Result == 1)
            //    CurrentShapeImage.Image = (Image)pictureBox1.Image.Clone();
            //else if (confirm.Result == 2)
            //{
            //    string name = new Guid().ToString();

            //    IOHelper.SaveImage((Image)pictureBox1.Image.Clone(), ImageUrl);
            //}
            //else
            //    return;

            if (xtraTabControl1.SelectedTabPageIndex == 0)
            {
                _selection = new Rectangle(pointArray[0][0].X, pointArray[0][0].Y, pointArray[0][1].X - pointArray[0][0].X, pointArray[0][1].Y - pointArray[0][0].Y);

                Image img = pictureBox1.Image.Crop(_selection);
                if (img == null)
                {
                    _selecting = false;
                    return;
                }
                // Fit shape to the picturebox:
                pictureBox1.Image = img.Fit2PictureBox(pictureBox1);
                imageHandler.CurrentBitmap = (Bitmap)pictureBox1.Image.Clone();
                CurrentImage = (Image)pictureBox1.Image.Clone();
                return;
            }
            LocalMessageBus.Send(this, new EditImage(CurrentShapeImage));
            IOHelper.SaveImage((Image)pictureBox1.Image.Clone(), ImageUrl);
        }

        private void btnReset_Click(object sender, EventArgs e)
        {
            spinEdit2.Value = 0;
            spinEdit1.Value = 0;
            pictureBox1.Image = (Image)CurrentImageOld.Clone();
            CurrentImage = (Image)CurrentImageOld.Clone();
            imageHandler.CurrentBitmap = (Bitmap)CurrentImage;
        }

        private void btnOk_Click(object sender, EventArgs e)
        {
            CurrentShapeImage.Image = (Image)pictureBox1.Image.Clone();
            LocalMessageBus.Send(this, new EditImage(CurrentShapeImage));
            //File.Delete(ImageUrl);

            if (File.Exists(ImageUrl))
                IOHelper.SetFileAttribute(ImageUrl, FileAttributes.Normal);
            IOHelper.SaveImage((Image)pictureBox1.Image.Clone(), ImageUrl);
            Close();
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void tbarCantrast_EditValueChanged(object sender, EventArgs e)
        {
            spinEdit2.Value = tbarCantrast.Value;
        }

        private void spinEdit2_EditValueChanged(object sender, EventArgs e)
        {
            tbarCantrast.Value = Convert.ToInt32(spinEdit2.Value);
            imageHandler.RestorePrevious();
            imageHandler.SetContrast(tbarCantrast.Value);
            PictureBoxImage();
        }

        private void ClearDraw()
        {
            drawingList = new DShapeList();
            drawingListUndo = new DShapeList();
            tempPoint = new DShapeList();
            pointViewList = new DShapeList();
            notchangeList = new DShapeList();
            notchangeListUndo = new DShapeList();

            pointCollection = new ArrayList();

            regionCollection = new NewRegion();
            regionCollectionUndo = new NewRegion();
            pointArray = new PointArrayCollection();
            pointArrayUndo = new PointArrayCollection();

            regionArrayCollection = new NewRegionArray();
            regionArrayCollectionUndo = new NewRegionArray();
            drawImageType = new TypeI();
            drawImageTypeUndo = new TypeI();
            newType = ImageType.Empty;

            //picked = false;
            changed = false;
            mouseMove = false;
            eraser = false;
            regionIndex = 0;

            this.pictureBox1.Invalidate();
        }
        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            try
            {
                if (this.xtraTabControl1.SelectedTabPageIndex != 0 && drawingList.Count == 0)
                {
                    return;
                }
                if (this.xtraTabControl1.SelectedTabPageIndex != 0 && drawingList.Count != 0)
                {
                    ClearDraw();
                    return;
                }
                Graphics displayGraphics = e.Graphics;
                if (drawingList.Count <= 0)
                {
                    int width = 100;
                    int height = 60;
                    Rectangle rec;
                    if (rdbOverallSignRatio.Checked)
                    {
                        width = ControlService.SignCombo.Current.Width * 2;
                        height = ControlService.SignCombo.Current.Height * 2;
                        if (width > pictureBox1.Width)
                        {
                            width = pictureBox1.Width / 2;
                            height = width * ControlService.SignCombo.Current.Height / ControlService.SignCombo.Current.Width;
                        }

                    }
                    if (rdbOriginalPictureRatio.Checked)
                    {
                        width = CurrentImage.Width / 2;
                        height = CurrentImage.Height / 2;
                        if (width > pictureBox1.Width)
                        {
                            width = pictureBox1.Width / 2;
                            height = width * CurrentImage.Height / CurrentImage.Width;
                        }
                    }

                    rec = new Rectangle(0, 0, width, height);
                    DrawRectangle(displayGraphics, rec);

                    //int m = regionIndex;

                    //m = (regionIndex + 1) % regionCollection.Count;		//循环下一项开始
                    int n = 0;
                    for (; n < regionCollection.Count; n++)
                    {
                        //if (m >= regionCollection.Count)
                        //    m = 0;
                        //if (regionCollection[m++].IsVisible(newPoint.StartP))
                        //{
                        pointViewList = new DShapeList();
                        regionIndex = 0;
                        tempMovePoint = new Point[pointArray[regionIndex].Length];
                        for (int j = 0; j < pointArray[regionIndex].Length; j++)
                        {
                            tempMovePoint[j] = pointArray[regionIndex][j];
                        }
                        PointView(regionIndex);
                        this.pictureBox1.Invalidate();
                        picked = true;
                        if (drawImageType[regionIndex] == (int)ImageType.Path)
                        {
                            mousePath = drawingList[regionIndex].pathChange(mousePath, true);
                        }
                        changed = false;
                        break;
                        //}
                        //else
                        //{
                        //    pointViewList = new DShapeList();
                        //    this.pictureBox1.Invalidate();
                        //    picked = false;
                        //}
                    }
                }
                switch (newType)
                {
                    case ImageType.Rectangle:

                        break;
                    case ImageType.Pick:
                        if (picked == true)
                        {
                            pointViewList.DrawList(displayGraphics);
                            if (changed == true && drawImageType[regionIndex] != (int)ImageType.Path)
                            {
                                if (drawImageType[regionIndex] == (int)ImageType.Rectangle)
                                {
                                    displayGraphics.DrawRectangle(new Pen(newColor, lineWidth), tempChangePoint.Rect);
                                }
                            }
                        }
                        break;
                }
                drawingList.DrawList(displayGraphics);
                SetStatus();
            }
            catch { }
            //this.pictureBox1.Invalidate();
            //Graphics g = e.Graphics;
            //g.DrawImage(imageHandler.CurrentBitmap, new Rectangle(this.AutoScrollPosition.X, this.AutoScrollPosition.Y, Convert.ToInt32(imageHandler.CurrentBitmap.Width * zoomFactor), Convert.ToInt32(imageHandler.CurrentBitmap.Height * zoomFactor)));
        }

        private void DrawRectangle(Graphics displayGraphics, Rectangle rec)
        {
            //Rectangle rec = new Rectangle(140, 130, 100, 60);

            displayGraphics.DrawRectangle(new Pen(newColor, lineWidth), rec);


            regionCollection.Add(new Region(rec));  //一定要先调用Rect，改变起点、终点
            drawImageType.Add(ImageType.Rectangle);
            tempPointArray = new Point[4] { new Point(rec.X, rec.Y), new Point(rec.X+rec.Width, rec.Y+rec.Height), 
                new Point(rec.X+rec.Width, rec.Y), new Point(rec.X, rec.Y+rec.Height) };
            pointArray.Add(tempPointArray);

            Point2Region(tempPointArray);
            regionArrayCollection.Add(tempRegion);

            drawingList.Add(new DHollowRectangle(tempPointArray, newColor, lineWidth));
            //this.statusBar.Panels[0].Text = "PickUp";
            newType = ImageType.Pick;
        }

        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            try
            {
                if (e.Button != MouseButtons.Left)
                    return;

                if (this.xtraTabControl1.SelectedTabPageIndex != 0)
                    return;

                newPoint = new MousePoint(e.X, e.Y);
                switch (newType)
                {
                    case ImageType.Pick:
                        if (picked == true)
                        {
                            for (int k = 0; k < regionArrayCollection[regionIndex].Length; k++)
                            {
                                if (regionArrayCollection[regionIndex][k].IsVisible(newPoint.StartP))
                                {
                                    pointIndex = k;
                                    changed = true;
                                    break;
                                }
                                else
                                    changed = false;
                            }
                            if (changed == true)
                                break;
                        }
                        int m = regionIndex;
                        if (picked == true)
                            m = (regionIndex + 1) % regionCollection.Count;		//循环下一项开始
                        int n = 0;
                        for (; n < regionCollection.Count; n++)
                        {
                            if (m >= regionCollection.Count)
                                m = 0;
                            if (regionCollection[m++].IsVisible(newPoint.StartP))
                            {
                                pointViewList = new DShapeList();
                                regionIndex = m - 1;
                                tempMovePoint = new Point[pointArray[regionIndex].Length];
                                for (int j = 0; j < pointArray[regionIndex].Length; j++)
                                {
                                    tempMovePoint[j] = pointArray[regionIndex][j];
                                }
                                PointView(regionIndex);
                                this.pictureBox1.Invalidate();
                                picked = true;
                                if (drawImageType[regionIndex] == (int)ImageType.Path)
                                {
                                    mousePath = drawingList[regionIndex].pathChange(mousePath, true);
                                }
                                changed = false;
                                break;
                            }
                            else
                            {
                                //pointViewList = new DShapeList();
                                //this.pictureBox1.Invalidate();
                                picked = false;
                            }
                        }
                        break;
                }
            }
            catch
            { }
        }

        private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            try
            {
                if (this.xtraTabControl1.SelectedTabPageIndex != 0)
                    return;

                if (e.Button == MouseButtons.None && regionArrayCollection.Count > 0)
                {
                    Point btn = new Point(e.X, e.Y);
                    if (regionCollection[0].IsVisible(btn))
                    {
                        Cursor = Cursors.SizeAll;
                    }
                    else
                        Cursor = Cursors.Default;
                    if (picked)
                    {
                        for (int k = 0; k < regionArrayCollection[0].Length; k++)
                        {
                            if (regionArrayCollection[0][k].IsVisible(btn))
                            {
                                if (k < 2)
                                    Cursor = Cursors.SizeNWSE;
                                else
                                    Cursor = Cursors.SizeNESW;
                            }
                            //else
                            //    Cursor = Cursors.Default;
                        }
                    }
                }

                if (e.Button != MouseButtons.Left)
                    return;

                int width = ControlService.SignCombo.Current.Width;
                int height = ControlService.SignCombo.Current.Height;
                if (rdbOriginalPictureRatio.Checked)
                {
                    height = CurrentImage.Height;
                    width = CurrentImage.Width;
                }
                newPoint.EndX = e.X;
                newPoint.EndY = e.Y;
                if (rdbOverallSignRatio.Checked
                    && changed == true
                    && drawImageType[regionIndex] != (int)ImageType.Path
                    )
                {
                    if (pointIndex == 2)
                    {
                        int x = pointArray[regionIndex][3].X + (width * (pointArray[regionIndex][3].Y - e.Y)) / height;
                        newPoint.EndX = x;
                    }
                    if (pointIndex == 3)
                    {
                        int y = pointArray[regionIndex][2].Y + (height * (pointArray[regionIndex][2].X - e.X)) / width;
                        newPoint.EndY = y;
                    }
                    //newPoint.EndY = e.Y;
                    //tempChangePoint.StartP = new Point(tempChangePoint.StartP.X, tempChangePoint.EndX - ((width * (tempChangePoint.EndY - e.Y)) / height));
                    //tempChangePoint.EndY = tempChangePoint.StartP.Y + ((height * (e.X - tempChangePoint.StartP.X)) / width);
                }
                //this.statusBar.Panels[1].Text = "Point:" + e.X.ToString() + "," + e.Y.ToString();
                switch (newType)
                {
                    case ImageType.Pick:
                        if (picked == true && changed != true)
                        {
                            mouseMove = true;
                            int MoveX = newPoint.EndP.X - newPoint.StartP.X;
                            int MoveY = newPoint.EndP.Y - newPoint.StartP.Y;
                            RegionMove(regionIndex, MoveX, MoveY);
                            if (drawImageType[regionIndex] != (int)ImageType.Path)
                            {
                                drawingList[regionIndex].pointchange(pointArray[regionIndex]);
                            }
                            else
                            {
                                regionPath = (GraphicsPath)mousePath.Clone();
                                Matrix translateMatrix = new Matrix();
                                translateMatrix.Translate(MoveX, MoveY);
                                regionPath.Transform(translateMatrix);
                                drawingList[regionIndex].pathChange(regionPath, false);
                            }
                            PointChange(regionIndex);


                        }
                        if (changed == true && drawImageType[regionIndex] != (int)ImageType.Path)
                        {
                            mouseMove = true;

                            //if (pointIndex < 2)
                            pointArray[regionIndex][pointIndex] = newPoint.EndP;
                            //else
                            //{
                            //    if(pointIndex =2)
                            //        pointArray[regionIndex][0] =new Point(newPoint.EndP.
                            //}
                            if (pointIndex < 2)
                            {
                                tempChangePoint = new MousePoint(pointArray[regionIndex][1 - pointIndex].X, pointArray[regionIndex][1 - pointIndex].Y);
                                tempChangePoint.EndX = pointArray[regionIndex][pointIndex].X;
                                if (rdbOverallSignRatio.Checked || rdbOriginalPictureRatio.Checked)
                                {

                                    //tempChangePoint.StartP.X+e.X-tempChangePoint.StartP.X
                                    tempChangePoint.EndY = tempChangePoint.StartP.Y + ((height * (e.X - tempChangePoint.StartP.X)) / width); // pointArray[regionIndex][pointIndex].Y;
                                }
                                else
                                    tempChangePoint.EndY = pointArray[regionIndex][pointIndex].Y;
                                regionCollection[regionIndex] = new Region(tempChangePoint.Rect);
                                if (pointIndex == 0)
                                {
                                    pointArray[0][0] = tempChangePoint.Rect.Location;
                                    pointArray[0][1] = new Point(tempChangePoint.StartP.X + tempChangePoint.Rect.Width, tempChangePoint.EndP.Y);

                                    pointArray[0][2] = new Point(tempChangePoint.EndX, tempChangePoint.EndP.Y);
                                    pointArray[0][3] = new Point(tempChangePoint.StartP.X + tempChangePoint.Rect.Width, tempChangePoint.Rect.Location.Y);
                                }
                                else
                                {
                                    pointArray[0][0] = tempChangePoint.Rect.Location;
                                    pointArray[0][1] = new Point(tempChangePoint.EndX, tempChangePoint.EndY);
                                    pointArray[0][2] = new Point(tempChangePoint.StartP.X + tempChangePoint.Rect.Width, tempChangePoint.StartP.Y);
                                    pointArray[0][3] = new Point(tempChangePoint.StartP.X, tempChangePoint.EndY);

                                }
                            }
                            if (pointIndex == 3)
                            {
                                tempChangePoint = new MousePoint(pointArray[regionIndex][3].X, pointArray[regionIndex][3].Y);
                                tempChangePoint.EndX = pointArray[regionIndex][2].X;
                                //if (rdbOverallSignRatio.Checked)
                                //{
                                //    tempChangePoint.StartP =new Point(tempChangePoint.StartP.X, tempChangePoint.EndY + ((height * (tempChangePoint.EndX - e.X)) / width));
                                //    //tempChangePoint.EndY = tempChangePoint.StartP.Y + ((height * (tempChangePoint.StartP.X-e.X)) / width);
                                //}
                                //else
                                tempChangePoint.EndY = pointArray[regionIndex][2].Y;
                                regionCollection[regionIndex] = new Region(tempChangePoint.Rect);
                                pointArray[0][0] = tempChangePoint.Rect.Location;
                                pointArray[0][1] = new Point(tempChangePoint.StartP.X + tempChangePoint.Rect.Width, tempChangePoint.EndP.Y);

                                pointArray[0][2] = new Point(tempChangePoint.EndX, tempChangePoint.EndY);
                                pointArray[0][3] = newPoint.EndP;// new Point(tempChangePoint.StartP.X, tempChangePoint.StartP.Y);// newPoint.EndP;
                                if (rdbOverallSignRatio.Checked || rdbOriginalPictureRatio.Checked)
                                    pointArray[0][3] = new Point(tempChangePoint.StartP.X, tempChangePoint.EndY + ((height * (tempChangePoint.EndX - e.X)) / width));// newPoint.EndP;
                            }
                            if (pointIndex == 2)
                            {
                                tempChangePoint = new MousePoint(pointArray[regionIndex][2].X, pointArray[regionIndex][2].Y);
                                tempChangePoint.EndX = pointArray[regionIndex][3].X;
                                tempChangePoint.EndY = pointArray[regionIndex][3].Y;



                                regionCollection[regionIndex] = new Region(tempChangePoint.Rect);

                                pointArray[0][0] = tempChangePoint.Rect.Location;
                                pointArray[0][1] = new Point(tempChangePoint.StartP.X + tempChangePoint.Rect.Width, tempChangePoint.EndP.Y);

                                pointArray[0][2] = new Point(tempChangePoint.StartP.X + tempChangePoint.Rect.Width, tempChangePoint.StartP.Y);
                                pointArray[0][3] = new Point(tempChangePoint.EndX, tempChangePoint.EndY);

                            }



                            drawingList[regionIndex].pointchange(pointArray[regionIndex]);
                            PointChange(regionIndex);
                        }
                        break;
                }
                pictureBox1.Invalidate();
                SetStatus();
            }
            catch
            { }
        }

        private void SetStatus()
        {
            var arr = pointArray[0];
            lblStatus.Text = "Location:" + arr[0].X + "," + arr[0].Y + ";  Width: "
                            + (arr[1].X - arr[0].X).ToString() + ";  Height: " + (arr[1].Y - arr[0].Y).ToString();
        }

        private void pictureBox1_MouseUp(object sender, MouseEventArgs e)
        {
            try
            {
                switch (newType)
                {
                    case ImageType.Pick:
                        if (picked == true && mouseMove == true && changed != true)
                        {
                            int MoveX = newPoint.EndP.X - newPoint.StartP.X;
                            int MoveY = newPoint.EndP.Y - newPoint.StartP.Y;
                            regionCollection[regionIndex].Translate(MoveX, MoveY);
                            foreach (Region r in regionArrayCollection[regionIndex])
                            {
                                r.Translate(MoveX, MoveY);
                            }
                            if (drawImageType[regionIndex] == (int)ImageType.Path)
                            {
                                Matrix translateMatrix = new Matrix();
                                translateMatrix.Translate(MoveX, MoveY);
                                mousePath.Transform(translateMatrix);
                                drawingList[regionIndex].pathChange(mousePath, false);
                            }
                        }
                        if (changed == true && mouseMove == true && drawImageType[regionIndex] != (int)ImageType.Path)
                        {
                            int MoveX = newPoint.EndP.X - newPoint.StartP.X;
                            int MoveY = newPoint.EndP.Y - newPoint.StartP.Y;
                            regionArrayCollection[regionIndex][pointIndex].Translate(MoveX, MoveY);
                            //RegionChange(regionIndex);
                            if (drawImageType[regionIndex] == (int)ImageType.Rectangle
                                || drawImageType[regionIndex] == (int)ImageType.FillRectangle
                                || drawImageType[regionIndex] == (int)ImageType.Ellipse
                                || drawImageType[regionIndex] == (int)ImageType.FillEllipse)
                            {
                                pointArray[regionIndex][0] = tempChangePoint.StartP;
                                pointArray[regionIndex][1] = tempChangePoint.EndP;
                                drawingList[regionIndex].pointchange(pointArray[regionIndex]);
                                Point2Region(pointArray[regionIndex]);
                                regionArrayCollection[regionIndex] = tempRegion;
                            }
                        }
                        mouseMove = false;
                        break;
                }
                this.pictureBox1.Invalidate();
            }
            catch
            { }
        }

        private void Point2Region(Point[] p)
        {
            Point[] point = new Point[p.Length];
            int j = 0;
            foreach (Point newp in p)
            {
                point[j++] = newp;
            }
            tempRegion = new Region[p.Length];
            for (int i = 0; i < p.Length; i++)
            {
                point[i].Offset(-(int)(2 * lineWidth), -(int)(2 * lineWidth));
                Rectangle r = new Rectangle(point[i], new Size((int)(4 * lineWidth), (int)(4 * lineWidth)));
                Region rr = new Region(r);
                tempRegion[i] = rr;
            }
        }

        private void RegionMove(int index, int x, int y)
        {
            for (int i = 0; i < pointArray[index].Length; i++)
            {
                pointArray[index][i].X = tempMovePoint[i].X + x;
                pointArray[index][i].Y = tempMovePoint[i].Y + y;
            }
        }

        private void PointView(int index)
        {
            Point tempPoint2;
            foreach (Point tempPoint in pointArray[index])
            {
                tempPoint2 = tempPoint;
                tempPoint.Offset(-(int)(2 * lineWidth), -(int)(2 * lineWidth));
                tempPoint2.Offset((int)(2 * lineWidth), (int)(2 * lineWidth));
                pointViewList.Add(new DHollowRectangle(new Point[] { tempPoint, tempPoint2 }, Color.DarkRed, 1));
                tempPoint.Offset((int)(2 * lineWidth), (int)(2 * lineWidth));
            }
        }
        private void PointChange(int index)
        {
            Point tempPoint2;
            for (int i = 0; i < pointArray[index].Length; i++)
            {
                tempPoint2 = pointArray[index][i];
                pointArray[index][i].Offset(-(int)(2 * lineWidth), -(int)(2 * lineWidth));
                tempPoint2.Offset((int)(2 * lineWidth), (int)(2 * lineWidth));
                pointViewList[i].pointchange(new Point[] { pointArray[index][i], tempPoint2 });
                pointArray[index][i].Offset((int)(2 * lineWidth), (int)(2 * lineWidth));
            }
        }

        private void pictureBox1_MouseEnter(object sender, EventArgs e)
        {
            //if (newType != ImageType.Eraser && newType != ImageType.Pick)
            //    this.Cursor = System.Windows.Forms.Cursors.Cross;
            //else
            //    this.Cursor = System.Windows.Forms.Cursors.Default;
        }

        private void pictureBox1_MouseLeave(object sender, EventArgs e)
        {
            this.Cursor = System.Windows.Forms.Cursors.Default;
        }

        private void xtraTabControl1_SelectedPageChanged(object sender, DevExpress.XtraTab.TabPageChangedEventArgs e)
        {
            this.pictureBox1.Invalidate();
            lblStatus.Visible = xtraTabControl1.SelectedTabPageIndex == 0;
        }

        private void rdbNormal_CheckedChanged(object sender, EventArgs e)
        {
            ClearDraw();
            pictureBox1.Invalidate();
        }
    }
}
