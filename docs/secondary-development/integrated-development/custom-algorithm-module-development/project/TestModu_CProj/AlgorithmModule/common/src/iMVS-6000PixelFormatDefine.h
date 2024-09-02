/***************************************************************************************************
*
* 版权信息：版权所有 (c) 2016, 杭州海康机器人技术有限公司, 保留所有权利
*
* 文件名称：iMVS-6000PixelFormatDefine.h
* 摘    要: iMVS-6000像素格式定义头文件
*
* 当前版本：1.0.0.0
* 作    者: zhangzhen5-应用软件组
* 日    期：2017-4-25 18:49:02
* 备    注：新建
****************************************************************************************************/
#ifndef IMVS_6000PIXELFORMATDEFINE_H__ // 2017-4-25 18:49:49
#define IMVS_6000PIXELFORMATDEFINE_H__

//===================================================
// 像素格式整体分类
//===================================================
const static unsigned int IMVS_PIX_MONO                                    = 0x01000000;
const static unsigned int IMVS_PIX_RGB                                     = 0x02000000;
const static unsigned int IMVS_PIX_COLOR                                   = 0x02000000;
const static unsigned int IMVS_PIX_CUSTOM                                  = 0x80000000;
const static unsigned int IMVS_PIX_COLOR_MASK                              = 0xFF000000;

//===================================================
// 像素格式每像素占位
//===================================================
const static unsigned int IMVS_PIX_OCCUPY1BIT                              = 0x00010000;
const static unsigned int IMVS_PIX_OCCUPY2BIT                              = 0x00020000;
const static unsigned int IMVS_PIX_OCCUPY4BIT                              = 0x00040000;
const static unsigned int IMVS_PIX_OCCUPY8BIT                              = 0x00080000;
const static unsigned int IMVS_PIX_OCCUPY12BIT                             = 0x000C0000;
const static unsigned int IMVS_PIX_OCCUPY16BIT                             = 0x00100000;
const static unsigned int IMVS_PIX_OCCUPY24BIT                             = 0x00180000;
const static unsigned int IMVS_PIX_OCCUPY32BIT                             = 0x00200000;
const static unsigned int IMVS_PIX_OCCUPY36BIT                             = 0x00240000;
const static unsigned int IMVS_PIX_OCCUPY48BIT                             = 0x00300000;
const static unsigned int IMVS_PIX_EFFECTIVE_PIXEL_SIZE_MASK               = 0x00FF0000;
const static unsigned int IMVS_PIX_EFFECTIVE_PIXEL_SIZE_SHIFT              = 16;
const static unsigned int IMVS_PIX_ID_MASK                                 = 0x0000FFFF;
const static unsigned int IMVS_PIX_COUNT                                   = 0x46 ;

//===================================================
// 像素格式详细定义
//===================================================
const static unsigned int IMVS_PIX_MONO1P                      = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY1BIT | 0x0037);
const static unsigned int IMVS_PIX_MONO2P                      = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY2BIT | 0x0038);
const static unsigned int IMVS_PIX_MONO4P                      = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY4BIT | 0x0039);
const static unsigned int IMVS_PIX_MONO8                       = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY8BIT | 0x0001);
const static unsigned int IMVS_PIX_MONO8_SIGNED                = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY8BIT  | 0x0002);
const static unsigned int IMVS_PIX_MONO10                      = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY16BIT | 0x0003);
const static unsigned int IMVS_PIX_MONO10_PACKED               = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY12BIT | 0x0004);
const static unsigned int IMVS_PIX_MONO12                      = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY16BIT | 0x0005);
const static unsigned int IMVS_PIX_MONO12_PACKED               = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY12BIT | 0x0006);
const static unsigned int IMVS_PIX_MONO14                      = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY16BIT | 0x0025);
const static unsigned int IMVS_PIX_MONO16                      = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY16BIT | 0x0007);

const static unsigned int IMVS_PIX_BAYGR8                      = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY8BIT | 0x0008);
const static unsigned int IMVS_PIX_BAYRG8                      = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY8BIT | 0x0009);
const static unsigned int IMVS_PIX_BAYGB8                      = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY8BIT | 0x000A);
const static unsigned int IMVS_PIX_BAYBG8                      = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY8BIT | 0x000B);
const static unsigned int IMVS_PIX_BAYGR10                     = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY16BIT | 0x000C);
const static unsigned int IMVS_PIX_BAYRG10                     = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY16BIT | 0x000D);
const static unsigned int IMVS_PIX_BAYGB10                     = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY16BIT | 0x000E);
const static unsigned int IMVS_PIX_BAYBG10                     = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY16BIT | 0x000F);
const static unsigned int IMVS_PIX_BAYGR12                     = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY16BIT | 0x0010);
const static unsigned int IMVS_PIX_BAYRG12                     = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY16BIT | 0x0011);
const static unsigned int IMVS_PIX_BAYGB12                     = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY16BIT | 0x0012);
const static unsigned int IMVS_PIX_BAYBG12                     = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY16BIT | 0x0013);
const static unsigned int IMVS_PIX_BAYGR10_PACKED              = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY12BIT | 0x0026);
const static unsigned int IMVS_PIX_BAYRG10_PACKED              = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY12BIT | 0x0027);
const static unsigned int IMVS_PIX_BAYGB10_PACKED              = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY12BIT | 0x0028);
const static unsigned int IMVS_PIX_BAYBG10_PACKED              = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY12BIT | 0x0029);
const static unsigned int IMVS_PIX_BAYGR12_PACKED              = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY12BIT | 0x002A);
const static unsigned int IMVS_PIX_BAYRG12_PACKED              = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY12BIT | 0x002B);
const static unsigned int IMVS_PIX_BAYGB12_PACKED              = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY12BIT | 0x002C);
const static unsigned int IMVS_PIX_BAYBG12_PACKED              = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY12BIT | 0x002D);
const static unsigned int IMVS_PIX_BAYGR16                     = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY16BIT | 0x002E);
const static unsigned int IMVS_PIX_BAYRG16                     = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY16BIT | 0x002F);
const static unsigned int IMVS_PIX_BAYGB16                     = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY16BIT | 0x0030);
const static unsigned int IMVS_PIX_BAYBG16                     = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY16BIT | 0x0031);

const static unsigned int IMVS_PIX_RGB8_PACKED                 = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY24BIT | 0x0014);
const static unsigned int IMVS_PIX_BGR8_PACKED                 = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY24BIT | 0x0015);
const static unsigned int IMVS_PIX_RGBA8_PACKED                = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY32BIT | 0x0016);
const static unsigned int IMVS_PIX_BGRA8_PACKED                = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY32BIT | 0x0017);
const static unsigned int IMVS_PIX_RGB10_PACKED                = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY48BIT | 0x0018);
const static unsigned int IMVS_PIX_BGR10_PACKED                = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY48BIT | 0x0019);
const static unsigned int IMVS_PIX_RGB12_PACKED                = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY48BIT | 0x001A);
const static unsigned int IMVS_PIX_BGR12_PACKED                = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY48BIT | 0x001B);
const static unsigned int IMVS_PIX_RGB16_PACKED                = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY48BIT | 0x0033);
const static unsigned int IMVS_PIX_RGB10V1_PACKED              = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY32BIT | 0x001C);
const static unsigned int IMVS_PIX_RGB10V2_PACKED              = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY32BIT | 0x001D);
const static unsigned int IMVS_PIX_RGB12V1_PACKED              = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY36BIT | 0X0034);
const static unsigned int IMVS_PIX_RGB565_PACKED               = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY16BIT | 0x0035);
const static unsigned int IMVS_PIX_BGR565_PACKED               = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY16BIT | 0X0036);

const static unsigned int IMVS_PIX_YUV411_PACKED               = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY12BIT | 0x001E); // 等同于const static unsigned int IMVS_PIX_YUV411_8_UYYVYY
const static unsigned int IMVS_PIX_YUV422_PACKED               = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY16BIT | 0x001F); // 等同于const static unsigned int IMVS_PIX_YUV422_8_UYVY
const static unsigned int IMVS_PIX_YUV422_YUYV_PACKED          = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY16BIT | 0x0032); // 等同于const static unsigned int IMVS_PIX_YUV422_8
const static unsigned int IMVS_PIX_YUV444_PACKED               = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY24BIT | 0x0020); // 等同于const static unsigned int IMVS_PIX_YUV8_UYV
const static unsigned int IMVS_PIX_YCBCR8_CBYCR                = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY24BIT | 0x003A);
const static unsigned int IMVS_PIX_YCBCR422_8                  = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY16BIT | 0x003B);
const static unsigned int IMVS_PIX_YCBCR422_8_CBYCRY           = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY16BIT | 0x0043);
const static unsigned int IMVS_PIX_YCBCR411_8_CBYYCRYY         = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY12BIT | 0x003C);
const static unsigned int IMVS_PIX_YCBCR601_8_CBYCR            = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY24BIT | 0x003D);
const static unsigned int IMVS_PIX_YCBCR601_422_8              = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY16BIT | 0x003E);
const static unsigned int IMVS_PIX_YCBCR601_422_8_CBYCRY       = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY16BIT | 0x0044);
const static unsigned int IMVS_PIX_YCBCR601_411_8_CBYYCRYY     = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY12BIT | 0x003F);
const static unsigned int IMVS_PIX_YCBCR709_8_CBYCR            = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY24BIT | 0x0040);
const static unsigned int IMVS_PIX_YCBCR709_422_8              = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY16BIT | 0x0041);
const static unsigned int IMVS_PIX_YCBCR709_422_8_CBYCRY       = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY16BIT | 0x0045);
const static unsigned int IMVS_PIX_YCBCR709_411_8_CBYYCRYY     = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY12BIT | 0x0042);

const static unsigned int IMVS_PIX_RGB8_PLANAR                 = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY24BIT | 0x0021);
const static unsigned int IMVS_PIX_RGB10_PLANAR                = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY48BIT | 0x0022);
const static unsigned int IMVS_PIX_RGB12_PLANAR                = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY48BIT | 0x0023);
const static unsigned int IMVS_PIX_RGB16_PLANAR                = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY48BIT | 0x0024);

// 算法组新增像素格式
const static unsigned int IMVS_PIX_HSV_PLANAR                  = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY8BIT | 0x0100);
const static unsigned int IMVS_PIX_HSI_PLANAR                  = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY8BIT | 0x0101);
const static unsigned int IMVS_PIX_YUV_PLANAR                  = (IMVS_PIX_COLOR | IMVS_PIX_OCCUPY8BIT | 0x0102);
const static unsigned int IMVS_PIX_MONO8_SIGNED_PLANAR         = (IMVS_PIX_MONO | IMVS_PIX_OCCUPY8BIT | 0x0103);



//===================================================
// 算法平台预备像素格式
//===================================================
const static unsigned int IMVS_PIX_Jpeg                        (IMVS_PIX_CUSTOM | IMVS_PIX_OCCUPY24BIT | 0x0001);
const static unsigned int IMVS_PIX_Bmp                         (IMVS_PIX_CUSTOM | IMVS_PIX_OCCUPY32BIT | 0x0002);



#endif // IMVS-6000PIXELFORMATDEFINE_H__

