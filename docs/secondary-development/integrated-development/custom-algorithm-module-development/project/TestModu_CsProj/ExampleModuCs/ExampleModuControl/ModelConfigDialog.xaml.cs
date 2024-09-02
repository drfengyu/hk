using Apps.Data;
using Apps.XmlParser.ParamTab;
using HikExternalCall.ImageProcess;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;
using VMControls.BaseInterface;
using VMControls.RenderInterface;
using VMControls.WPF;

namespace TestModuControl
{
    /// <summary>
    /// ModelConfigDialog.xaml 的交互逻辑
    /// </summary>
    public partial class ModelConfigDialog : Window, INotifyPropertyChanged
    {
        #region INotifyPropertyChanged Members

        public event PropertyChangedEventHandler PropertyChanged;

        public void NotifyPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }
        #endregion

        #region 字段
        private double mViewScale = 1;
        private double imageScale = 1;
        private int imageWidth = 0;
        private int imageHeight = 0;
        private bool isDrawing = false;
        private IImageData curImage;
        private double positionX = 0;
        private double positionY = 0;
        private Point startPoint;
        private Point endPoint;
        private bool isEdit = false;
        #endregion

        #region 属性
        public double PositionX
        {
            get { return positionX; }
            set
            {
                if (positionX != value)
                {
                    positionX = value;
                    NotifyPropertyChanged("PositionX");
                }
            }
        }

        public double PositionY
        {
            get { return positionY; }
            set
            {
                if (positionY != value)
                {
                    positionY = value;
                    NotifyPropertyChanged("PositionY");
                }
            }
        }

        /// <summary>
        /// 模块参数通信接口
        /// </summary>
        public IParamsConfig ModuleParam { get; set; }

        /// <summary>
        /// 参数数据源
        /// </summary>
        public object ParamSource
        {
            get { return (object )GetValue(ParamSourceProperty); }
            set { SetValue(ParamSourceProperty, value); }
        }

        public static readonly DependencyProperty ParamSourceProperty =
            DependencyProperty.Register("ParamSource", typeof(object), typeof(ModelConfigDialog), new PropertyMetadata(null));
        #endregion

        #region 方法
        public ModelConfigDialog()
        {
            InitializeComponent();
        }

        public ModelConfigDialog(bool status)
        {
            InitializeComponent();
            isEdit = status;
        }

        private void AddImgButton_Click(object sender, RoutedEventArgs e)
        {
            string path = string.Empty;
            ImageData tempImage = new ImageData();
            tempImage.PixelFormat = PixelFormats.Gray8;
            try
            {
                ImageProcessManager.GetMono8ImageDataByFileDialog(ref tempImage.Width, ref tempImage.Height, ref tempImage.ImageBuffer, ref path);
                ChangeImage(tempImage);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "加载图片失败", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void ChangeImage(ImageData tempImage)
        {
            if (tempImage.ImageBuffer != null)
            {
                imageView.IImageData = tempImage;
                curImage = tempImage;
                imageWidth = tempImage.Width;
                imageHeight = tempImage.Height;
                mViewScale = ((double)tempImage.Width / tempImage.Height) / (mROIView.ActualWidth / mROIView.ActualHeight);
                stf.CenterX = mROIView.ActualWidth / 2;
                stf.CenterY = mROIView.ActualHeight / 2;
                if (mViewScale < 1)
                {
                    stf.ScaleX = mViewScale;
                    stf.ScaleY = 1;
                    imageScale = tempImage.Height / mROIView.ActualHeight;
                }
                else
                {
                    stf.ScaleX = 1;
                    stf.ScaleY = 1 / mViewScale;
                    imageScale = tempImage.Width / mROIView.ActualWidth;
                }
            }
        }

        private void Finish_OnClick(object sender, RoutedEventArgs e)
        {
            DialogResult = true;
            Close();
        }

        private void OnMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            if (!isDrawing)
            {
                return;
            }
            startPoint = new Point(PositionX, PositionY);
            e.Handled = true;
        }

        private void OnMouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            if (!isDrawing)
            {
                return;
            }
            endPoint = new Point(PositionX, PositionY);
            float fX = (float)(startPoint.X + endPoint.X) / 2;
            float fY = (float)(startPoint.Y + endPoint.Y) / 2;
            float fW = (float)Math.Abs(endPoint.X - startPoint.X);
            float fH = (float)Math.Abs(endPoint.Y - startPoint.Y);
            DrawBox(fX, fY, fW, fH);

            isDrawing = false;
            BtnDraw.Content = "绘制矩形";
            mView.Cursor = Cursors.Arrow;
            mView.Visibility = Visibility.Collapsed;
            e.Handled = true;
        }

        private void DrawBox(float fX, float fY, float fW, float fH, float fA = 0)
        {
            MyBox box = new MyBox()
            {
                CenterPoint = new Point(fX, fY),
                Width = fW,
                Height = fH,
                Angle = fA,
                Opacity = 1,
                Stroke = "#ff00ccff",
                StrokeThickness = 1,
            };
            imageView.DrawShapes(box);

            tbCenterX.Text = box.CenterPoint.X.ToString("N2");
            tbCenterY.Text = box.CenterPoint.Y.ToString("N2");
            tbWidth.Text = box.Width.ToString("N2");
            tbHeight.Text = box.Height.ToString("N2");
            tbAngle.Text = box.Angle.ToString("N2");

        }

        private int ConvertColor(byte bAlpha, byte bR, byte bG, byte bB)
        {
            int argb = bAlpha << 24;
            argb += bR << 16;
            argb += bG << 8;
            argb += bB;
            return argb;
        }

        private void OnMouseMove(object sender, MouseEventArgs e)
        {
            e.Handled = true;
            if (curImage == null)
            {
                xVal.Content = "--";
                yVal.Content = "--";
                return;
            }
            var p = e.GetPosition(mView);
            if (mViewScale < 1)
            {
                PositionX = p.X * mViewScale * imageScale;
                PositionY = p.Y * imageScale;
            }
            else
            {
                PositionX = p.X * imageScale;
                PositionY = p.Y / mViewScale * imageScale;
            }
            xVal.Content = PositionX.ToString("N2");
            yVal.Content = PositionY.ToString("N2");
        }

        private void DrawButton_Click(object sender, RoutedEventArgs e)
        {
            if (isDrawing)
            {
                isDrawing = false;
                BtnDraw.Content = "绘制矩形";
                mView.Cursor = Cursors.Arrow;
                mView.Visibility = Visibility.Collapsed;
            }
            else
            {
                isDrawing = true;
                BtnDraw.Content = "取消绘制";
                mView.Cursor = Cursors.Cross;
                imageView.IImageData = null;
                imageView.IImageData = curImage;
                mView.Visibility = Visibility.Visible;
            }
        }

        private void ReDrawButton_Click(object sender, RoutedEventArgs e)
        {
            MyBox box = new MyBox()
            {
                CenterPoint = new Point(float.Parse(tbCenterX.Text), float.Parse(tbCenterY.Text)),
                Width = float.Parse(tbWidth.Text),
                Height = float.Parse(tbHeight.Text),
                Angle = float.Parse(tbAngle.Text),
                Opacity = 1,
                Stroke = "#ff00ccff",
                StrokeThickness = 1,
            };
            imageView.IImageData = null;
            imageView.IImageData = curImage;
            imageView.DrawShapes(box);
        }

        private void Create_OnClick(object sender, RoutedEventArgs e)
        {
            try
            {
                if (ModuleParam != null)
                {
                    ModelData model = new ModelData();
                    InitModelData(model);
                    ModelPanel.CreateModel(ModuleParam, model);
                    byte[] pointsBuffer = (ModuleParam as IUserBytesData)["GetPointSet"];
                    StructDefine.IMVS_POINT_F_Set points = new StructDefine.IMVS_POINT_F_Set();
                    points.point = new StructDefine.IMVS_POINT_F[StructDefine.MAX_Point_NUM];
                    int size = Marshal.SizeOf(points);
                    IntPtr allocIntPtr = Marshal.AllocHGlobal(size);
                    try
                    {
                        Marshal.Copy(pointsBuffer, 0, allocIntPtr, size);
                        points = (StructDefine.IMVS_POINT_F_Set)Marshal.PtrToStructure(allocIntPtr, 
                            typeof(StructDefine.IMVS_POINT_F_Set));
                    }
                    catch (Exception ex)
                    {
                        throw ex;
                    }
                    finally
                    {
                        Marshal.FreeHGlobal(allocIntPtr);
                    }
                    MyPointSet pointSet = new MyPointSet();
                    pointSet.PointNum = (int)points.num;
                    pointSet.PointList = new List<Point>();
                    pointSet.Stroke = "#ff00ff00";
                    pointSet.Opacity = 1;
                    for (int i = 0; i < points.num; i++)
                    {
                        Point point = new Point(points.point[i].x, points.point[i].y);
                        pointSet.PointList.Add(point);
                    }
                    imageView.DrawShapes(pointSet);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void InitModelData(ModelData model)
        {
            model.BoxCenterX = float.Parse(tbCenterX.Text);
            model.BoxCenterY = float.Parse(tbCenterY.Text);
            model.BoxWidth = float.Parse(tbWidth.Text);
            model.BoxHeight = float.Parse(tbHeight.Text);
            model.BoxAngle = float.Parse(tbAngle.Text);

            model.ImageWidth = curImage.Width;
            model.ImageHeight = curImage.Height;
            model.ImageBuffer = curImage.Buffer;
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            if (isEdit)
            {
                ModelData model = new ModelData();
                try
                {
                    ModelPanel.GetModel(ModuleParam, model);
                    if (model.ImageBuffer != null && model.ImageWidth * model.ImageHeight == model.ImageBuffer.Length)
                    {
                        ImageData tempImage = new ImageData();
                        tempImage.PixelFormat = PixelFormats.Gray8;
                        tempImage.Width = model.ImageWidth;
                        tempImage.Height = model.ImageHeight;
                        tempImage.ImageBuffer = model.ImageBuffer;
                        ChangeImage(tempImage);
                        DrawBox(model.BoxCenterX, model.BoxCenterY, model.BoxWidth, model.BoxHeight, model.BoxAngle);
                        MyPointSet pointSet = new MyPointSet();
                        pointSet.PointNum = model.ModelPoints.Count; ;
                        pointSet.PointList = new List<Point>();
                        pointSet.Stroke = "#ff00ff00";
                        pointSet.Opacity = 1;
                        for (int i = 0; i < model.ModelPoints.Count; i++)
                        {
                            Point point = new Point(model.ModelPoints[i].x, model.ModelPoints[i].y);
                            pointSet.PointList.Add(point);
                        }
                        imageView.DrawShapes(pointSet);
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
        }
        #endregion

    }

    public class MyBox : IRectangle
    {
        public Point CenterPoint { get; set; }

        public double Width { get; set; }

        public double Height { get; set; }

        public double Angle { get; set; }

        public double SkewAngleX { get; set; }

        public double SkewAngleY { get; set; }

        public string Fill { get; set; }

        public double StrokeThickness { get; set; }

        public string ToolTip { get; set; }

        public double Opacity { get; set; }

        public string Stroke { get; set; }
    }

    public class MyPoint : IPoint
    {
        public Point Point { get; set; }

        public string Fill { get; set; }

        public double StrokeThickness { get; set; }

        public string ToolTip { get; set; }

        public double Opacity { get; set; }

        public string Stroke { get; set; }
    }

    public class MyPointSet : IPointSet
    {
        public int PointNum { get; set; }

        public List<Point> PointList { get; set; }

        public string Fill { get; set; }

        public double StrokeThickness { get; set; }

        public string ToolTip { get; set; }

        public double Opacity { get; set; }

        public string Stroke { get; set; }
    }
}
