using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using IMVSGroupCs;
using OpenCvSharp;
using VM.PlatformSDKCS;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private IMVSGroupTool groupTool { set; get; }

        /// <summary>
        /// 选择Group路径
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog fileDialog = new OpenFileDialog();
            fileDialog.Filter = "VM Gro File|*.gro*";
            DialogResult openFileRes = fileDialog.ShowDialog();
            if (openFileRes==DialogResult.OK)
            {
                textBox1.Text = fileDialog.FileName;
            }
        }
        /// <summary>
        /// 导入Group
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button3_Click(object sender, EventArgs e)
        {
            string strMsg = null;
            try
            {
                groupTool = IMVSGroupTool.LoadIndependentGroup(textBox1.Text);
                vmSingleModuleSetConfigControl1.ModuleSource = groupTool;
                
            }
            catch (VmException ex)
            {
                strMsg = "加载Group失败.异常码:"+Convert.ToString(ex.errorCode,16);
                listBox1.Items.Add(strMsg);
                listBox1.TopIndex = listBox1.Items.Count - 1;
                return;
            }
            strMsg = "加载Group成功.";
            listBox1.Items.Add(strMsg);
            listBox1.TopIndex = listBox1.Items.Count - 1;
        }
        /// <summary>
        /// 导出Group
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button2_Click(object sender, EventArgs e)
        {
            groupTool.Save();
            listBox1.Items.Add("导出Group成功.");
            listBox1.TopIndex = listBox1.Items.Count - 1;
        }
        /// <summary>
        /// 执行一次
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button4_Click(object sender, EventArgs e)
        {
            groupTool.Run();

            listBox1.Items.Add("执行Group成功.");
            listBox1.TopIndex = listBox1.Items.Count - 1;

            vmRenderControl1.ModuleSource = groupTool;

            //通过Group获取渲染结果和数据结果

            string radius = groupTool.ModuResult.GetOutputFloat("out").pFloatVal[0].ToString();

            //ImageBaseData_V2 imageBaseData_V2 = groupTool.ModuResult.GetOutputImageV2("ImageData");
            ImageBaseData_V2 imageBaseData_V2 = groupTool.ModuResult.GetOutputImageV2("ImageData0");
            int width = imageBaseData_V2.Width;
            int height = imageBaseData_V2.Height;
            IntPtr imageByte = imageBaseData_V2.ImageData;
            VMPixelFormat pixelFormat = imageBaseData_V2.Pixelformat;

            //通过模块获取渲染结果和数据结果

            //IMVSLineFindModuCs.IMVSLineFindModuTool lineFindModuTool = (IMVSLineFindModuCs.IMVSLineFindModuTool)groupTool["直线查找1"];
            //vmRenderControl1.ModuleSource = lineFindModuTool;

            //string strGroLineX = lineFindModuTool.ModuResult.OutputLine.StartPoint.X.ToString();

            listBox1.Items.Add($"角度:{ radius},图像宽:{width},高:{height},格式:{pixelFormat}");
            listBox1.TopIndex = listBox1.Items.Count - 1;
        }

        private void button5_Click(object sender, EventArgs e)
        {
            //Group无图像源的输入图,用opencv从本地读图
            Mat matImage = Cv2.ImRead(Application.StartupPath + "/img/0304720-IMG_1.jpg", ImreadModes.Grayscale);

            uint dataLen = (uint)(matImage.Width * matImage.Height);
            ImageBaseData_V2 image = new ImageBaseData_V2(matImage.Data,dataLen,matImage.Cols,matImage.Rows,VMPixelFormat.VM_PIXEL_MONO_08);
            groupTool.ModuParams.SetInputImage_V2("ImageData0",image);


            //Group无图像源的输入图,用bitmap从本地读图
            //Bitmap bmp = new Bitmap(Application.StartupPath+"/img/0304720-IMG_1.jpg.jpg");
            //BitmapData bitmapData = bmp.LockBits(new Rectangle(0, 0, bmp.Width, bmp.Height), ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            //uint datalen = (uint)(bitmapData.Width * bitmapData.Height);
            //ImageBaseData_V2 image1 = new ImageBaseData_V2(bitmapData.Scan0,datalen,bitmapData.Width,bitmapData.Height,VMPixelFormat.VM_PIXEL_MONO_08);
            //groupTool.ModuParams.SetInputImage_V2("ImageData0",image1);
            //bmp.UnlockBits(bitmapData);
        }
    }
}
