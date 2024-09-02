using Apps.Data;
using Hik.Xml;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Media;
using VMControls.BaseInterface;

namespace Apps.XmlParser.ParamTab
{
    public class ModelPanel : NameValueItem
    {

        #region Field
        public AlgorithmTabRoot SubAlgorithmTabRoot;
        #endregion

        #region Property
        /// <summary>
        /// 模型参数
        /// </summary>
        public AlgorithmTabRoot SubAlgorithmTabRootA
        {
            get
            {
                if (SubAlgorithmTabRoot == null)
                {
                    SubAlgorithmTabRoot = new AlgorithmTabRoot();
                }
                return SubAlgorithmTabRoot;
            }
        }
        #endregion

        #region 方法
        public static void CreateModel(IParamsConfig paramsConfig, ModelData model)
        {
            if (paramsConfig == null || model == null)
            {
                return;
            }
            /*(paramsConfig as IUserStringData)["SetImageWidth"] = model.ImageWidth.ToString();
            (paramsConfig as IUserStringData)["SetImageHeight"] = model.ImageHeight.ToString();
            (paramsConfig as IUserBytesData)["SetImageData"] = model.ImageBuffer;
            StructDefine.IMVS_ROI_BOX box = new StructDefine.IMVS_ROI_BOX
            {
                fRoiCenterX = model.BoxCenterX,
                fRoiCenterY = model.BoxCenterY,
                fRoiWidth = model.BoxWidth,
                fRoiHeight = model.BoxHeight,
                fRoiAngle = model.BoxAngle
            };
            int size = Marshal.SizeOf(box);
            byte[] buffer = new byte[size];
            IntPtr bufferIntPtr = IntPtr.Zero;
            try
            {
                bufferIntPtr = Marshal.AllocHGlobal(size);
                Marshal.StructureToPtr(box, bufferIntPtr, true);
                Marshal.Copy(bufferIntPtr, buffer, 0, size);
            }
            catch (Exception ex)
            {
                throw ex;
            }
            finally
            {
                Marshal.FreeHGlobal(bufferIntPtr);
            }
            (paramsConfig as IUserBytesData)["SetRoiData"] = buffer;
            (paramsConfig as IUserStringData)["ModelCreate"] = "";*/
        }

        public static void GetModel(IParamsConfig paramsConfig, ModelData model)
        {
            if (paramsConfig == null || model == null)
            {
                return;
            }
           /*model.ImageWidth = int.Parse((paramsConfig as IUserStringData)["GetImageWidth"]);
            model.ImageHeight = int.Parse((paramsConfig as IUserStringData)["GetImageHeight"]);
            model.ImageBuffer = (paramsConfig as IUserBytesData)["GetImageData"];

            byte[] roiBuffer = (paramsConfig as IUserBytesData)["GetRoiData"];
            StructDefine.IMVS_ROI_BOX box = new StructDefine.IMVS_ROI_BOX();
            int roiSize = Marshal.SizeOf(box);
            IntPtr roiIntPtr = Marshal.AllocHGlobal(roiSize);
            try
            {
                Marshal.Copy(roiBuffer, 0, roiIntPtr, roiSize);
                box = (StructDefine.IMVS_ROI_BOX)Marshal.PtrToStructure(roiIntPtr,
                    typeof(StructDefine.IMVS_ROI_BOX));
            }
            catch (Exception ex)
            {
                throw ex;
            }
            finally
            {
                Marshal.FreeHGlobal(roiIntPtr);
            }
            model.BoxCenterX = box.fRoiCenterX;
            model.BoxCenterY = box.fRoiCenterY;
            model.BoxWidth = box.fRoiWidth;
            model.BoxHeight = box.fRoiHeight;
            model.BoxAngle = box.fRoiAngle;

            byte[] pointsBuffer = (paramsConfig as IUserBytesData)["GetPointSet"];
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
            model.ModelPoints = new List<StructDefine.IMVS_POINT_F>();
            for (int i = 0; i < points.num; i++)
            {
                model.ModelPoints.Add(points.point[i]);
            }*/
        }

        /// <summary>
        /// 绘制显示缩略图
        /// </summary>
        /// <param name="model"></param>
        public static void CreateModelImageData(ModelData model)
        {
            if (model == null)
            {
                return;
            }
            int width = 300;
            int height = 216;
            if (model.ImageBuffer != null && model.ModelPoints != null && model.ModelPoints.Count != 0)
            {
                int minX = model.ImageWidth;
                int minY = model.ImageHeight;
                int maxX = 0;
                int maxY = 0;
                GetOutLineBorder(model, ref minX, ref minY, ref maxX, ref maxY);

                maxX = Math.Min(maxX, model.ImageWidth);
                maxY = Math.Min(maxY, model.ImageHeight);
                minX = Math.Max(minX, 0);
                minY = Math.Max(minY, 0);

                //实际模型在图像中的宽高
                int nModelWidth = (maxX - minX);
                int nModelHeight = (maxY - minY);

                //显示轮廓缩略图的宽高
                int nShowWidth = 0;
                int nShowHeight = 0;

                double hwRate = (double)nModelHeight / (double)nModelWidth;

                //获取实际坐标转换比例 
                if (hwRate <= 1.0
                    && (width * hwRate < height) /*显示窗口不溢出*/)
                {
                    nShowWidth = width;
                    nShowHeight = (int)(nShowWidth * hwRate);
                }
                else
                {
                    nShowHeight = height;
                    nShowWidth = (int)(nShowHeight / hwRate);
                }

                if (model.ModelImageData == null)
                {
                    model.ModelImageData = new ImageData();
                }

                model.ModelImageData.ImageBuffer = new byte[nShowWidth * nShowHeight * 3];
                model.ModelImageData.Height = nShowHeight;
                model.ModelImageData.Width = nShowWidth;
                model.ModelImageData.PixelFormat = PixelFormats.Rgb24;
                //填充模型图像
                for (int i = 0; i < nShowHeight; i++)
                {
                    for (int j = 0; j < nShowWidth; j++)
                    {
                        int nImageX = (int)(minX + j / (double)nShowWidth * nModelWidth);
                        int nImageY = (int)(minY + i / (double)nShowHeight * nModelHeight);
                        model.ModelImageData.ImageBuffer[3 * (i * nShowWidth + j)] = model.ImageBuffer[nImageY * model.ImageWidth + nImageX];
                        model.ModelImageData.ImageBuffer[3 * (i * nShowWidth + j) + 1] = model.ImageBuffer[nImageY * model.ImageWidth + nImageX];
                        model.ModelImageData.ImageBuffer[3 * (i * nShowWidth + j) + 2] = model.ImageBuffer[nImageY * model.ImageWidth + nImageX];
                    }
                }

                //绘制点
                foreach (StructDefine.IMVS_POINT_F point in model.ModelPoints)
                {
                    int nShowX = (int)((point.x - minX) / nModelWidth * nShowWidth + 0.5);
                    int nShowY = (int)((point.y - minY) / nModelHeight * nShowHeight + 0.5);

                    try
                    {
                        int nIndex = 3 * (nShowY * nShowWidth + nShowX);
                        //越界直接catch捕捉 不再判断
                        SetImagePointGreen(model.ModelImageData.ImageBuffer, nIndex);

                        nIndex = 3 * ((nShowY + 1) * nShowWidth + nShowX);
                        SetImagePointGreen(model.ModelImageData.ImageBuffer, nIndex);

                        //防止偏移至下一行
                        if (nShowX < nShowWidth - 1)
                        {
                            nIndex = 3 * (nShowY * nShowWidth + nShowX + 1);
                            SetImagePointGreen(model.ModelImageData.ImageBuffer, nIndex);

                            nIndex = 3 * ((nShowY + 1) * nShowWidth + nShowX + 1);
                            SetImagePointGreen(model.ModelImageData.ImageBuffer, nIndex);
                        }
                    }
                    catch
                    {

                    }
                }
            }
        }

        private static void SetImagePointGreen(byte[] imageBuffer, int index)
        {
            if ((index + 2) < imageBuffer.Length)
            {
                imageBuffer[index] = 0;
                imageBuffer[index + 1] = 255;
                imageBuffer[index + 2] = 0;
            }
        }

        /// <summary>
        /// 获取模型图像区域
        /// </summary>
        /// <param name="model"></param>
        /// <param name="minX"></param>
        /// <param name="minY"></param>
        /// <param name="maxX"></param>
        /// <param name="maxY"></param>
        private static void GetOutLineBorder(ModelData model, ref int minX, ref int minY, ref int maxX, ref int maxY)
        {
            if (model == null)
            {
                return;
            }
            
            foreach (StructDefine.IMVS_POINT_F point in model.ModelPoints)
            {

                if (point.x < minX)
                {
                    minX = (int)point.x;
                }
                if (point.y < minY)
                {
                    minY = (int)point.y;
                }
                if (point.x > maxX)
                {
                    maxX = (int)Math.Min(point.x + 1, model.ImageWidth);
                }
                if (point.y > maxY)
                {
                    maxY = (int)Math.Min(point.y + 1, model.ImageHeight);
                }
            }
        }

        #endregion
    }

    /// <summary>
    /// 模型数据
    /// </summary>
    public class ModelData : BaseNode
    {
        public float BoxWidth;
        public float BoxHeight;
        public float BoxCenterX;
        public float BoxCenterY;
        public float BoxAngle;

        public int ImageWidth;
        public int ImageHeight;
        public byte[] ImageBuffer;

        public List<StructDefine.IMVS_POINT_F> ModelPoints { get; set; }

        public ImageData ModelImageData { get; set; }
    }

    public class StructDefine
    {
        public const int MAX_Point_NUM = 32;
        public struct IMVS_POINT_F
        {
            public float x;          // x坐标
            public float y;          // y坐标
        };

        public struct IMVS_POINT_F_Set
        {
            public uint num;        //点数
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = MAX_Point_NUM)]
            public IMVS_POINT_F[] point;   //坐标点
        };

        // 矩形ROI结构体
        public struct IMVS_ROI_BOX
        {
            public float fRoiCenterX;
            public float fRoiCenterY;
            public float fRoiWidth;
            public float fRoiHeight;
            public float fRoiAngle;
        };

    }
}
