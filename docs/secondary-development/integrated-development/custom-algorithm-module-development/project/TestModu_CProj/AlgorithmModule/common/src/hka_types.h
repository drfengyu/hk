/***************************************************************************************************
* 
* 版权信息：版权所有 (c) 2010-2018, 杭州海康威视软件有限公司, 保留所有权利
*
* 文件名称：hka_types.h
* 摘    要：海康威视算法组件基础数据结构体声明文件
* 
* 当前版本：1.2.5
* 作    者：武晓阳
* 日    期：2019年3月1日
* 备    注：空enum数据类型增加NONE定义，保证跨平台编译正常；
* 
* 历史版本：1.2.4
* 作    者：武晓阳
* 日    期：2018年6月20日
* 备    注：定义空的enum数据类型，保证HKA_MEM_TAB_V2使用；
* 
* 历史版本：1.2.3
* 作    者：武晓阳
* 日    期：2018年6月14日
* 备    注：增加HKA_MEM_TAB_V2，统一各个平台，建议采用；
* 
* 历史版本：1.2.2
* 作    者：武晓阳
* 日    期：2018年6月12日
* 备    注：增加单通道16位浮点数图像和32位浮点数图像；
* 
* 历史版本：1.2.1
* 作    者：武晓阳
* 日    期：2018年5月14日
* 备    注：支持ASIC C Model要求的内存结构（1. 增加1byte对齐、不需要对齐宏；2. 增加ASIC MEM_TAB）；
*           内存表个数和顺序不再定义，由算法库自行定义；
* 
* 历史版本：1.1.1
* 作    者：武晓阳
* 日    期：2017年9月1日
* 备    注：1 增加unknown图像格式，让用户定制
* 
* 历史版本：1.1.0
* 作    者：武晓阳
* 日    期：2017年8月1日
* 备    注：1 增加图像格式（丰富YUV类型，增加CMYK、YCCK格式）
*           2 扩展多平台定义宏
* 
* 历史版本：1.0.1
* 作    者：武晓阳
* 日    期：2017年5月23日
* 备    注：1 增加HKA_IMG_YUV_YUYV图像格式
*           2 与之前版本兼容
* 
* 历史版本：1.0.0
* 作    者：申琳
* 日    期：2015年5月26日
* 备    注：1 修改HKA_MEM_TAB_LIST为HKA_MEM_TAB_TYPE
*           2 增加相关数据详细注释
* 
* 历史版本：0.9.0
* 作    者：申琳 武晓阳 戚红命 蔡巍伟
* 日    期：2015年5月20日
* 备    注：1 增加64位平台宏定义
*           2 增加加密相关错误码定义
*           3 增加矩阵数据类型枚举定义
*           4 增加了x86、arm和dsp平台的HKA_MEM_TAB_LIST定义
*
* 历史版本：0.2.0
* 作    者：蔡巍伟
* 日    期：2015年4月21日
* 备    注：以vca_base.h为基础，考虑数据结构的复用性定义初始版本
*
* 历史版本：0.1.0
* 作    者：全晓臣 邝宏武
* 日    期：2014年10月10日
* 备    注：初始版本
***************************************************************************************************/
#ifndef _HKA_TYPES_H_
#define _HKA_TYPES_H_


#ifdef __cplusplus
extern "C" {
#endif
    

/***************************************************************************************************
* 多平台64位宏定义
***************************************************************************************************/
#if (defined (_WIN64)                    \
    || defined (_LINUX64)                \
    || defined (_MAC64)                  \
    || defined (_IOS64)                  \
    || defined (_ANDROID64)              \
    || defined (ARCHS_STANDARD_64_BIT))  \
	|| defined(_AMD64_)
#define _HKA_SYS64
#endif


/***************************************************************************************************
* 基本数据类型的定义
***************************************************************************************************/
typedef signed char         HKA_S08;
typedef unsigned char       HKA_U08;
typedef signed short        HKA_S16;
typedef unsigned short      HKA_U16;
typedef signed int          HKA_S32;
typedef unsigned int        HKA_U32;
typedef float               HKA_F32;
typedef double              HKA_F64;

#if defined(_WIN32) || defined (_WIN64)
    typedef signed __int64      HKA_S64;
    typedef unsigned __int64    HKA_U64;
#else
    typedef signed long long    HKA_S64;
    typedef unsigned long long  HKA_U64;
#endif

#if defined (_HKA_SYS64)
    typedef HKA_U64      HKA_SZT;
#else
    typedef HKA_U32      HKA_SZT;
#endif

#ifndef HKA_VOID
#define HKA_VOID         void
#endif


/***************************************************************************************************
* 复数, re: 实部, im: 虚部
***************************************************************************************************/
typedef struct _HKA_SC08
{
    HKA_S08  re;
    HKA_S08  im;
}HKA_SC08;

typedef struct _HKA_SC16
{
    HKA_S16  re;
    HKA_S16  im;
}HKA_SC16;

typedef struct _HKA_UC16
{
    HKA_U16  re;
    HKA_U16  im;
}HKA_UC16;

typedef struct _HKA_SC32
{
    HKA_S32  re;
    HKA_S32  im;
}HKA_SC32;

typedef struct _HKA_FC32
{
    HKA_F32  re;
    HKA_F32  im;
}HKA_FC32;

typedef struct _HKA_FC64
{
    HKA_F64  re;
    HKA_F64  im;
}HKA_FC64;


/***************************************************************************************************
* 点
***************************************************************************************************/
//点(短整型）
typedef struct _HKA_POINT_S
{
    HKA_S16 x;          // x坐标
    HKA_S16 y;          // y坐标
}HKA_POINT_S;

//点(整型) 
typedef struct _HKA_POINT_I
{
    HKA_S32 x;          // x坐标
    HKA_S32 y;          // y坐标
}HKA_POINT_I;

//点(浮点型) 
typedef struct _HKA_POINT_F
{
    HKA_F32 x;          // x坐标
    HKA_F32 y;          // y坐标
}HKA_POINT_F;


/***************************************************************************************************
* 矩形
***************************************************************************************************/
//矩形(短整型)
typedef struct _HKA_RECT_S
{
    HKA_S16 x;          //矩形左上角X轴坐标
    HKA_S16 y;          //矩形左上角Y轴坐标
    HKA_S16 width;      //矩形宽度
    HKA_S16 height;     //矩形高度
}HKA_RECT_S;

//矩形(整型)
typedef struct _HKA_RECT_I
{
    HKA_S32 x;          //矩形左上角X轴坐标
    HKA_S32 y;          //矩形左上角Y轴坐标
    HKA_S32 width;      //矩形宽度
    HKA_S32 height;     //矩形高度
}HKA_RECT_I;

//矩形(浮点型)
typedef struct _HKA_RECT_F
{
    HKA_F32 x;          //矩形左上角X轴坐标
    HKA_F32 y;          //矩形左上角Y轴坐标
    HKA_F32 width;      //矩形宽度
    HKA_F32 height;     //矩形高度
}HKA_RECT_F;


/***************************************************************************************************
* 包围盒
***************************************************************************************************/
//包围盒(短整型),宽度为(right - left + 1), 高度为(bottom - top + 1)
typedef struct _HKA_BOX_S
{
    HKA_S16 left;       //左边界
    HKA_S16 top;        //上边界
    HKA_S16 right;      //右边界
    HKA_S16 bottom;     //下边界
}HKA_BOX_S;

//包围盒(整型)
typedef struct _HKA_BOX_I
{
    HKA_S32 left;       //左边界
    HKA_S32 top;        //上边界
    HKA_S32 right;      //右边界
    HKA_S32 bottom;     //下边界
}HKA_BOX_I;

//包围盒(浮点型)
typedef struct _HKA_BOX_F
{
    HKA_F32 left;       //左边界
    HKA_F32 top;        //上边界
    HKA_F32 right;      //右边界
    HKA_F32 bottom;     //下边界
}HKA_BOX_F;


/***************************************************************************************************
* 多边形
***************************************************************************************************/
//多边形最大顶点数
#define HKA_MAX_VERTEX_NUM   (10)

//多边形(短整型)
typedef struct _HKA_POLYGON_S
{
    HKA_S32       vertex_num;                  //顶点数
    HKA_POINT_S   point[HKA_MAX_VERTEX_NUM];   //顶点
}HKA_POLYGON_S;

//多边形(整型)
typedef struct _HKA_POLYGON_I
{
    HKA_S32       vertex_num;                  //顶点数
    HKA_POINT_I   point[HKA_MAX_VERTEX_NUM];   //顶点
}HKA_POLYGON_I;

//多边形(浮点型)
typedef struct _HKA_POLYGON_F
{
    HKA_S32       vertex_num;                  //顶点数
    HKA_POINT_F   point[HKA_MAX_VERTEX_NUM];   //顶点
}HKA_POLYGON_F;


/***************************************************************************************************
* 矢量
***************************************************************************************************/
//矢量（短整型）
typedef struct _HKA_VECTOR_S
{
    HKA_POINT_S   start_point;  //起点
    HKA_POINT_S   end_point;    //终点
}HKA_VECTOR_S;

//矢量（整型）
typedef struct _HKA_VECTOR_I
{
    HKA_POINT_I   start_point;  //起点
    HKA_POINT_I   end_point;    //终点
}HKA_VECTOR_I;

//矢量(浮点型)
typedef struct _HKA_VECTOR_F
{
    HKA_POINT_F   start_point;  //起点
    HKA_POINT_F   end_point;    //终点
}HKA_VECTOR_F;


/***************************************************************************************************
* 图像宽高
***************************************************************************************************/
//尺寸(短整型)
typedef struct _HKA_SIZE_S
{
    HKA_S16 width;      // 宽度
    HKA_S16 height;     // 高度
}HKA_SIZE_S;

//尺寸(整型)
typedef struct _HKA_SIZE_I
{
    HKA_S32  width;     // 宽度
    HKA_S32  height;    // 高度
}HKA_SIZE_I;

//尺寸(浮点型)
typedef struct _HKA_SIZE_F
{
    HKA_F32  width;     // 宽度
    HKA_F32  height;    // 高度
}HKA_SIZE_F;


/***************************************************************************************************
* 内存管理器HKA_MEM_TAB结构体定义
***************************************************************************************************/
//内存对齐属性
typedef enum _HKA_MEM_ALIGNMENT
{
    HKA_MEM_ALIGN_NULL     = 0,   // 不需要对齐，不能在HKA_SIZE_ALIGN宏中使用
    HKA_MEM_ALIGN_1BYTE    = 1,
    HKA_MEM_ALIGN_4BYTE    = 4,
    HKA_MEM_ALIGN_8BYTE    = 8,
    HKA_MEM_ALIGN_16BYTE   = 16,
    HKA_MEM_ALIGN_32BYTE   = 32,
    HKA_MEM_ALIGN_64BYTE   = 64,
    HKA_MEM_ALIGN_128BYTE  = 128,
    HKA_MEM_ALIGN_256BYTE  = 256
}HKA_MEM_ALIGNMENT; 

#if ((defined DSP) || (defined _HIK_DSP_APP_))
//内存属性（从算法应用角度的复用性对内存进行分类）
typedef enum _HKA_MEM_ATTRS
{
    HKA_MEM_SCRATCH,                 //可复用内存，能在多路切换时有条件复用  
    HKA_MEM_PERSIST                  //不可复用内存
}HKA_MEM_ATTRS;

//内存分配空间（从内存分配的物理位置来分类）
typedef enum _HKA_MEM_SPACE
{
    HKA_MEM_EXTERNAL_PROG,           //外部程序存储区 
    HKA_MEM_INTERNAL_PROG,           //内部程序存储区 
    HKA_MEM_EXTERNAL_TILERED_DATA,   //外部Tilered数据存储区 
    HKA_MEM_EXTERNAL_CACHED_DATA,    //外部可Cache存储区 
    HKA_MEM_EXTERNAL_UNCACHED_DATA,  //外部不可Cache存储区
    HKA_MEM_INTERNAL_DATA,           //内部存储区 
    HKA_MEM_EXTERNAL_TILERED8 ,      //外部Tilered数据存储区8bit，Netra/Centaurus特有 
    HKA_MEM_EXTERNAL_TILERED16,      //外部Tilered数据存储区16bit，Netra/Centaurus特有 
    HKA_MEM_EXTERNAL_TILERED32 ,     //外部Tilered数据存储区32bit，Netra/Centaurus特有 
    HKA_MEM_EXTERNAL_TILEREDPAGE     //外部Tilered数据存储区page形式，Netra/Centaurus特有 
}HKA_MEM_SPACE;

//内存分配结构体 --> 建议采用HKA_MEM_TAB_V2版本
typedef struct _HKA_MEM_TAB
{
    HKA_SZT             size;        //以BYTE为单位的内存大小
    HKA_MEM_ALIGNMENT   alignment;   //内存对齐属性, 建议为128
    HKA_MEM_SPACE       space;       //内存分配空间 
    HKA_MEM_ATTRS       attrs;       //内存属性 
    HKA_VOID           *base;        //分配出的内存指针 
}HKA_MEM_TAB;

//内存表的个数（推荐的内存表排列顺序和数量，如不满足要求，可在算法库头文件中自行定义）
typedef enum _HKA_MEM_TAB_TYPE
{
    HKA_MEM_TAB_PERSIST      = 0,
    HKA_MEM_TAB_SCRATCH      = 1,
    HKA_MEM_TAB_SCRATCH_IRAM = 2,
    HKA_MEM_TAB_NUM          = 3
}HKA_MEM_TAB_TYPE;

#elif( (defined ARM) || (defined _HIK_ARM_APP_))

//内存属性（从算法应用角度的复用性对内存进行分类），暂为空，配合MEM_TAB_V2使用
typedef enum _HKA_MEM_ATTRS
{
    HKA_MEM_ATTRS_NONE  = -1          //空数据类型，请勿使用

}HKA_MEM_ATTRS;

//内存分配空间（从内存分配的物理位置来分类），暂为空，配合MEM_TAB_V2使用
typedef enum _HKA_MEM_SPACE
{
    HKA_MEM_SPACE_NONE  = -1          //空数据类型，请勿使用

}HKA_MEM_SPACE;

//内存分配结构体 --> 建议采用HKA_MEM_TAB_V2版本
typedef struct _HKA_MEM_TAB
{
    HKA_SZT             size;        //以BYTE为单位的内存大小
    HKA_MEM_ALIGNMENT   alignment;   //内存对齐属性, 建议为128 
    HKA_VOID           *base;        //分配出的内存指针 
}HKA_MEM_TAB;

//内存表的个数（推荐的内存表排列顺序和数量，如不满足要求，可在算法库头文件中自行定义）
typedef enum _HKA_MEM_TAB_TYPE
{
    HKA_MEM_TAB_PERSIST    = 0,
    HKA_MEM_TAB_SCRATCH    = 1,
    HKA_MEM_TAB_IVE_PHY    = 2,
    HKA_MEM_TAB_NUM        = 3
}HKA_MEM_TAB_TYPE;

#elif( (defined ASIC) || (defined _HIK_ASIC_MODEL_))

//内存属性（从算法应用角度的复用性对内存进行分类）
typedef enum _HKA_MEM_ATTRS
{
    HKA_MEM_SCRATCH,                 //可复用内存，能在多路切换时有条件复用  
    HKA_MEM_PERSIST                  //不可复用内存
}HKA_MEM_ATTRS;

//内存分配空间（从内存分配的物理位置来分类）
typedef enum _HKA_MEM_SPACE
{
    HKA_MEM_INTERNAL_RAM,            //片内随机读写存储区
    HKA_MEM_INTERNAL_ROM,            //片内只读存储区
    HKA_MEM_EXTERNAL_DDR             //片外DDR存储区
}HKA_MEM_SPACE;

//内存分配结构体 --> 建议采用HKA_MEM_TAB_V2版本
typedef struct _HKA_MEM_TAB
{
    HKA_SZT             size;        //ASIC中可以BYTE不对齐，C Model中为BYTE单位的存储区大小
    HKA_MEM_ALIGNMENT   alignment;   //内存对齐属性, 一般RAM/ROM不需要考虑对齐问题，DDR中要求16BYTE对齐
    HKA_MEM_SPACE       space;       //内存分配空间 
    HKA_MEM_ATTRS       attrs;       //内存属性 
    HKA_VOID           *base;        //分配出的内存指针 
}HKA_MEM_TAB;

#else//默认x86处理器

//内存属性（从算法应用角度的复用性对内存进行分类），暂为空，配合MEM_TAB_V2使用
typedef enum _HKA_MEM_ATTRS
{
    HKA_MEM_ATTRS_NONE  = -1          //空数据类型，请勿使用

}HKA_MEM_ATTRS;

//内存分配空间（从内存分配的物理位置来分类），暂为空，配合MEM_TAB_V2使用
typedef enum _HKA_MEM_SPACE
{
    HKA_MEM_SPACE_NONE  = -1          //空数据类型，请勿使用

}HKA_MEM_SPACE;

//内存分配结构体 --> 建议采用HKA_MEM_TAB_V2版本
typedef struct _HKA_MEM_TAB
{
    HKA_SZT             size;        //以BYTE为单位的内存大小
    HKA_MEM_ALIGNMENT   alignment;   //内存对齐属性, 建议为128 
    HKA_VOID           *base;        //分配出的内存指针 
}HKA_MEM_TAB;

//内存表的个数（推荐的内存表排列顺序和数量，如不满足要求，可在算法库头文件中自行定义）
typedef enum _HKA_MEM_TAB_TYPE
{
    HKA_MEM_TAB_PERSIST    = 0,
    HKA_MEM_TAB_SCRATCH    = 1,
    HKA_MEM_TAB_NUM        = 2
}HKA_MEM_TAB_TYPE;

#endif//((defined DSP) || (defined _HIK_DSP_APP_)) 


//内存分配结构体V2，所有平台都可以使用该结构体
typedef struct _HKA_MEM_TAB_V2
{
    HKA_SZT             size;        //以BYTE为单位的内存大小
    HKA_MEM_ALIGNMENT   alignment;   //内存对齐属性
    HKA_MEM_SPACE       space;       //内存分配空间的物理位置 
    HKA_MEM_ATTRS       attrs;       //内存使用属性 
    HKA_VOID           *base;        //分配出的内存指针 
}HKA_MEM_TAB_V2;


/***************************************************************************************************
* 图像结构体定义
***************************************************************************************************/
//图像格式（新的类型添加在最后面，保持前向兼容，每种格式按段长度100划分）
typedef enum _HKA_IMAGE_FORMAT
{
    //未知的，未定义数据格式。用户可以根据应用情况另外定义格式变量
    HKA_IMG_UNKNOWN             = 0,

    //----------------------------------------------------------------------------------------------
    //注：宽度width原则上是指所见图像水平像素点个数，
    //所以YUV图像宽度都以Y分量宽度为准，
    //RGB、RGBD、RGBA都以一个分量的宽度为准；
    //而bayer格式都当作一个通道处理，宽度为一行数据各分量宽度和。
    //注：行间距是指数据平面两行开始间隔的数据个数，
    //比如RGB 3平面格式，每个平面宽度为width，则行间距step >= width;
    //比如RGB 3通道交织格式，每个平面宽度为width，则行间距step >= width*3;
    //----------------------------------//----------------------------------------------------------
    //mono (0~99)                       //| bit  | type |   store position    |        step         |
    //mono8                             //----------------------------------------------------------
    HKA_IMG_MONO_08             = 1,    //| 8b   | U08  |        D0           |         S0          |
    //mono12                            //----------------------------------------------------------
    HKA_IMG_MONO_12             = 2,    //| 12b  | S16  |        D0           |         S0          |
    //mono16                            //----------------------------------------------------------
    HKA_IMG_MONO_16             = 3,    //| 16b  | U16  |        D0           |         S0          |
    //mono float 16bit                  //----------------------------------------------------------
    HKA_IMG_MONO_F16            = 4,    //| 16b  | F16  |        D0           |         S0          |
    //mono float 32bit                  //----------------------------------------------------------
    HKA_IMG_MONO_F32            = 5,    //| 32b  | F32  |        D0           |         S0          |
    //----------------------------------//----------------------------------------------------------
    //YUV (100~199)                     //| bit  | type |   store position    |        step         |
    //YUV420 Sx(U,V) = 2 Sy(U,V) = 2    //----------------------------------------------------------
    //I420 planar
    HKA_IMG_YUV_I420            = 100,  //| 8b   | U08  |    Y:D0,U:D1,V:D2   |  Y:S0,U:S1,V:S2     |
    //YUV420                            //----------------------------------------------------------
    //YV12 planar
    HKA_IMG_YUV_YV12            = 101,  //| 8b   | U08  |    Y:D0,V:D1,U:D2   |  Y:S0,V:S1,U:S2     |
    //YUV420                            //----------------------------------------------------------
    //NV12 UV packed
    HKA_IMG_YUV_NV12            = 102,  //| 8b   | U08  |    Y:D0,UV:D1       |  Y:S0,UV:S1         |
    //YUV422 Sx(U,V) = 1 Sy(U,V) = 2    //----------------------------------------------------------
    //planar
    HKA_IMG_YUV_422             = 103,  //| 8b   | U08  |    Y:D0,U:D1,V:D2   |  Y:S0,U:S1,V:S2     |
    //YUV422                            //----------------------------------------------------------
    //UYVY packed
    HKA_IMG_YUV_UYVY            = 104,  //| 8b   | U08  |    YUV:D0           |  YUV:S0             |
    //YUV444  Sx(U,V) = 1 Sy(U,V) = 1   //----------------------------------------------------------
    //planar
    HKA_IMG_YUV_444             = 105,  //| 8b   | U08  |    Y:D0,U:D1,V:D2   |  Y:S0,U:S1,V:S2     |
    //YUV422                            //----------------------------------------------------------
    //YUYV (YUY2) packed
    HKA_IMG_YUV_YUYV            = 106,  //| 8b   | U08  |    YUV:D0           |  YUV:S0             |
    //YUV422                            //----------------------------------------------------------
    //YVYU packed
    HKA_IMG_YUV_YVYU            = 107,  //| 8b   | U08  |    YUV:D0           |  YUV:S0             |
    //YUV422                            //----------------------------------------------------------
    //VYUY
    HKA_IMG_YUV_VYUY            = 108,  //| 8b   | U08  |    YUV:D0           |  YUV:S0             |
    //YUV420                            //----------------------------------------------------------
    //NV21 VU packed
    HKA_IMG_YUV_NV21            = 109,  //| 8b   | U08  |    Y:D0,VU:D1       |  Y:S0,VU:S1         |
    //YUV411 Sx(U,V) = 4 Sy(U,V) = 1    //----------------------------------------------------------
    //planar
    HKA_IMG_YUV_YUV411          = 130,  //| 8b   | U08  |    Y:D0,U:D1,V:D2   |  Y:S0,U:S1,V:S2     |
    //YUV411                            //----------------------------------------------------------
    //Y411 (Y41P) packed: U0 Y0 V0 Y1 U4 Y2 V4 Y3 Y4 Y5 Y6 Y8 
    HKA_IMG_YUV_Y41P            = 131,  //| 8b   | U08  |    YUV:D0           |  YUV:S0             |
    //YVU9 Sx(U,V) = 4 Sy(U,V) = 4      //----------------------------------------------------------
    //planar
    HKA_IMG_YUV_YVU9            = 140,  //| 8b   | U08  |    Y:D0,U:D1,V:D2   |  Y:S0,U:S1,V:S2     |
    //AYUV                              //----------------------------------------------------------
    //planar
    HKA_IMG_YUV_AYUV            = 150,  //| 8b   | U08  | A:D0,Y:D1,U:D2,V:D3 | A:S0,Y:S1,U:S2,V:S3 |
    //YUV440  Sx(U,V) = 1 Sy(U,V) = 2   //----------------------------------------------------------
    //planar
    HKA_IMG_YUV_440             = 180,  //| 8b   | U08  |    Y:D0,U:D1,V:D2   |  Y:S0,U:S1,V:S2     |
    //YUV424  Sx(U) = 2 Sy(V) = 2       //----------------------------------------------------------
    //planar
    HKA_IMG_YUV_424             = 181,  //| 8b   | U08  |    Y:D0,U:D1,V:D2   |  Y:S0,U:S1,V:S2     |
    //YUV442  Sy(U) = 2 Sx(V) = 2       //----------------------------------------------------------
    //planar
    HKA_IMG_YUV_442             = 182,  //| 8b   | U08  |    Y:D0,U:D1,V:D2   |  Y:S0,U:S1,V:S2     |
    //----------------------------------//----------------------------------------------------------
    //RGB (200~299)                     //| bit  | type |   store position    |        step         |
    //RBG 3 plane                       //----------------------------------------------------------
    HKA_IMG_RGB_RGB24_P3        = 200,  //| 8b   | U08  |    R:D0,G:D1,B:D2   |  R:S0,G:S1,B:S2     |
    //RGB 3 RGBRGB...                   //----------------------------------------------------------
    HKA_IMG_RGB_RGB24_C3        = 201,  //| 8b   | U08  |    RGB:D0           |  RGB:S0             |
    //RGB 4 plane(alpha)                //----------------------------------------------------------
    HKA_IMG_RGB_RGBA_P4         = 202,  //| 8b   | U08  | R:D0,G:D1,B:D2,A:D3 | R:S0,G:S1,B:S2,A:S3 |
    //RGB 4 RGBARGBA...(alpha)          //----------------------------------------------------------
    HKA_IMG_RGB_RGBA_C4         = 203,  //| 8b   | U08  |    RGBA:D0          |  RGBA:S0            |
    //RGB 4 plane(depth)                //----------------------------------------------------------
    HKA_IMG_RGB_RGBD_P4         = 204,  //| 8b   | U08  | R:D0,G:D1,B:D2,A:D3 | R:S0,G:S1,B:S2,A:S3 |
    //RGB 4 RGBDRGBD...(depth)          //----------------------------------------------------------
    HKA_IMG_RGB_RGBD_C4         = 205,  //| 8b   | U08  |    RGBA:D0          |  RGBA:S0            |
    //----------------------------------//----------------------------------------------------------
    //bayer (300~399)                   //| bit  | type |   store position    |        step         |
    //bayer GRGB 10bit                  //----------------------------------------------------------
    HKA_IMG_BAYER_GRBG_10       = 300,  //| 10b  | S16  |    GRBG:D0          |  GRBG:S0            |
    //bayer RGGB 10bit                  //----------------------------------------------------------
    HKA_IMG_BAYER_RGGB_10       = 301,  //| 10b  | S16  |    RGGB:D0          |  RGGB:S0            |
    //bayer RGGB 10bit                  //----------------------------------------------------------
    HKA_IMG_BAYER_BGGR_10       = 302,  //| 10b  | S16  |    BGGR:D0          |  BGGR:S0            |
    //bayer RGGB 10bit                  //----------------------------------------------------------
    HKA_IMG_BAYER_GBRG_10       = 303,  //| 10b  | S16  |    GBRG:D0          |  GBRG:S0            |
    //bayer RGGB 10bit                  //----------------------------------------------------------
    HKA_IMG_BAYER_GRBG_12       = 304,  //| 12b  | S16  |    GRBG:D0          |  GRBG:S0            |
    //bayer RGGB 10bit                  //----------------------------------------------------------
    HKA_IMG_BAYER_RGGB_12       = 305,  //| 12b  | S16  |    RGGB:D0          |  RGGB:S0            |
    //bayer RGGB 10bit                  //----------------------------------------------------------
    HKA_IMG_BAYER_BGGR_12       = 306,  //| 12b  | S16  |    BGGR:D0          |  BGGR:S0            |
    //bayer RGGB 10bit                  //----------------------------------------------------------
    HKA_IMG_BAYER_GBRG_12       = 307,  //| 12b  | S16  |    GBRG:D0          |  GBRG:S0            |
    //----------------------------------//----------------------------------------------------------
    //YCbCr (400~499)                   //| bit  | type |   store position    |        step         |
    //YCCK Sx(U,V) = 1 Sy(U,V) = 1      //----------------------------------------------------------
    //planar                            //----------------------------------------------------------
    HKA_IMG_YCCK_P4             = 400,  //| 8b   | U08  |Y:D0,Cb:D1,Cr:D2,K:D3|Y:S0,Cb:S1,Cr:S2,K:S3|
    //packed  C0 M0 Y0 K0 C1 M1 Y1 K1   //----------------------------------------------------------
    HKA_IMG_YCCK_C4             = 401,  //| 8b   | U08  |    YCCK:D0          |  YCCK:S0            |
    //----------------------------------//----------------------------------------------------------
    //CMYK (500~519)                    //| bit  | type |   store position    |        step         |
    //planar                            //----------------------------------------------------------
    HKA_IMG_CMYK_P4             = 500,  //| 8b   | U08  | C:D0,M:D1,Y:D2,K:D3 | C:S0,M:S1,Y:S2,K:S3 |
    //packed  C0 M0 Y0 K0 C1 M1 Y1 K1   //----------------------------------------------------------
    HKA_IMG_CMYK_C4             = 501   //| 8b   | U08  |    CMYK:D0          |  CMYK:S0            |
    //----------------------------------//----------------------------------------------------------
}HKA_IMAGE_FORMAT;

//图像格式表示结构体
typedef struct _HKA_IMAGE
{
    HKA_IMAGE_FORMAT    format;      //图像格式，按照数据类型HKA_IMAGE_FORMAT赋值
    HKA_S32             width;       //图像宽度
    HKA_S32             height;      //图像高度
    HKA_S32             step[4];     //行间距
    HKA_VOID           *data[4];     //数据存储地址
}HKA_IMAGE;


/***************************************************************************************************
* 矩阵结构体定义
***************************************************************************************************/
//HKA_MAT_TYPE类型分段符号
#define HKA_MAT_TYPE_SIGN   0x80000000

//图像格式（新的类型添加在最后面，保持前向兼容）
typedef enum _HKA_MAT_TYPE
{
    HKA_MAT_TYPE_01U     = 1,                           //无符号整型位宽1
    HKA_MAT_TYPE_08U     = 8,                           //无符号整型位宽8
    HKA_MAT_TYPE_16U     = 16,                          //无符号整型位宽16
    HKA_MAT_TYPE_32F     = 32,                          //单精度浮点型位宽32
    HKA_MAT_TYPE_08S     = (HKA_MAT_TYPE_SIGN | 8),     //有符号整型位宽8
    HKA_MAT_TYPE_16S     = (HKA_MAT_TYPE_SIGN | 16),    //有符号整型位宽16
    HKA_MAT_TYPE_32S     = (HKA_MAT_TYPE_SIGN | 32)     //有符号整型位宽32
}HKA_MAT_TYPE;

//矩阵定义
typedef struct _HKA_MAT
{
    HKA_MAT_TYPE type;      //矩阵元素的数据类型，按照数据类型HKA_MAT_TYPE赋值
    HKA_S32      step;      //行数据宽度（每行所占字节数）
    HKA_S32      rows;      //行
    HKA_S32      cols;      //列

    //数据指针联合结构体
    union
    {
        HKA_U08 *ptr;
        HKA_S16 *s;
        HKA_S32 *i;
        HKA_F32 *fl;
        HKA_F64 *db;
    }data;
}HKA_MAT;


/***************************************************************************************************
* 组件接口常用数据结构、宏定义
***************************************************************************************************/
//算法库接口设置、获取参数最大数目。
#define HKA_MAX_PARAM_NUM    (256)

//算法库接口设置、获取单个参数结构体，算法库内、库外都使用，公共模块不使用
typedef struct _HKA_KEY_PARAM
{
    HKA_S32 index;
    HKA_S32 value;
}HKA_KEY_PARAM;

//算法库接口设置、获取多个参数结构体。算法库内、库外都使用，公共模块不使用
typedef struct _HKA_KEY_PARAM_LIST
{
    HKA_S32        param_num;
    HKA_KEY_PARAM  param[HKA_MAX_PARAM_NUM];
}HKA_KEY_PARAM_LIST;

//设置配置参数类型（cfg_type），HKAXXX_SetConfig函数使用
typedef enum _HKA_SET_CFG_TYPE
{
    HKA_SET_CFG_SINGLE_PARAM    = 0x0001,    //单个参数
    HKA_SET_CFG_PARAM_LIST      = 0x0002,    //参数列表
    HKA_SET_CFG_DEFAULT_PARAM   = 0x0003,    //默认参数
    HKA_SET_CFG_RESTART_LIB     = 0x0004,    //重启算法库
    HKA_SET_CFG_CALLBACK        = 0x0005,    //回调函数
    HKA_SET_CFG_CHECK_PARAM     = 0x0006     //单个参数检测
}HKA_SET_CFG_TYPE;

//获取配置参数类型（cfg_type），HKAXXX_GetConfig函数使用
typedef enum _HKA_GET_CFG_TYPE
{
    HKA_GET_CFG_SINGLE_PARAM    = 0x0001,    //单个参数
    HKA_GET_CFG_PARAM_LIST      = 0x0002,    //整个参数表
    HKA_GET_CFG_VERSION         = 0x0003,    //版本信息
    HKA_GET_CFG_ABILITY         = 0x0004     //算法库能力集
}HKA_GET_CFG_TYPE;


/***************************************************************************************************
* 状态码
***************************************************************************************************/
//状态码数据类型
typedef int HKA_STATUS;    //组件接口函数返回值都定义为该类型

//函数返回状态类型
//算法库可以在库头文件中自定义状态类型，自定义状态类型值 < -1000。
typedef enum _HKA_STATUS_CODE
{
    //cpu指令集支持错误码
    HKA_STS_ERR_CPUID           = -29,    //cpu不支持优化代码中的指令集

    //内部模块返回的基本错误类型
    HKA_STS_ERR_STEP            = -28,    //数据step不正确（除HKA_IMAGE结构体之外）
    HKA_STS_ERR_DATA_SIZE       = -27,    //数据大小不正确（一维数据len，二维数据的HKA_SIZE）
    HKA_STS_ERR_BAD_ARG         = -26,    //参数范围不正确

    //算法库加密相关错误码定义
    HKA_STS_ERR_EXPIRE          = -25,    //算法库使用期限错误
    HKA_STS_ERR_ENCRYPT         = -24,    //加密错误

    //以下为组件接口函数使用的错误类型
    HKA_STS_ERR_CALL_BACK       = -23,    //回调函数出错
    HKA_STS_ERR_OVER_MAX_MEM    = -22,    //超过HKA限定最大内存
    HKA_STS_ERR_NULL_PTR        = -21,    //函数参数指针为空（共用）

    //检查HKA_KEY_PARAM、HKA_KEY_PARAM_LIST成员变量的错误类型
    HKA_STS_ERR_PARAM_NUM       = -20,    //param_num参数不正确
    HKA_STS_ERR_PARAM_VALUE     = -19,    //value参数不正确或者超出范围
    HKA_STS_ERR_PARAM_INDEX     = -18,    //index参数不正确

    //检查cfg_type, cfg_size, prc_type, in_size, out_size, func_type是否正确
    HKA_STS_ERR_FUNC_SIZE       = -17,    //子处理时输入、输出参数大小不正确
    HKA_STS_ERR_FUNC_TYPE       = -16,    //子处理类型不正确
    HKA_STS_ERR_PRC_SIZE        = -15,    //处理时输入、输出参数大小不正确
    HKA_STS_ERR_PRC_TYPE        = -14,    //处理类型不正确
    HKA_STS_ERR_CFG_SIZE        = -13,    //设置、获取参数输入、输出结构体大小不正确
    HKA_STS_ERR_CFG_TYPE        = -12,    //设置、获取参数类型不正确

    //检查HKA_IMAGE成员变量的错误类型
    HKA_STS_ERR_IMG_DATA_NULL   = -11,    //图像数据存储地址为空（某个分量）
    HKA_STS_ERR_IMG_STEP        = -10,    //图像宽高与step参数不匹配
    HKA_STS_ERR_IMG_SIZE        = -9,     //图像宽高不正确或者超出范围
    HKA_STS_ERR_IMG_FORMAT      = -8,     //图像格式不正确或者不支持

    //检查HKA_MEM_TAB成员变量的错误类型
    HKA_STS_ERR_MEM_ADDR_ALIGN  = -7,     //内存地址不满足对齐要求
    HKA_STS_ERR_MEM_SIZE_ALIGN  = -6,     //内存空间大小不满足对齐要求
    HKA_STS_ERR_MEM_LACK        = -5,     //内存空间大小不够
    HKA_STS_ERR_MEM_ALIGN       = -4,     //内存对齐不满足要求
    HKA_STS_ERR_MEM_NULL        = -3,     //内存地址为空

    //检查ability成员变量的错误类型
    HKA_STS_ERR_ABILITY_ARG     = -2,     //ABILITY存在无效参数

    //通用类型
    HKA_STS_ERR                 = -1,     //不确定类型错误（接口函数共用）
    HKA_STS_OK                  =  0,     //处理正确（接口函数共用）
    HKA_STS_WARNING             =  1      //警告

}HKA_STATUS_CODE;

#ifdef __cplusplus
}
#endif 

#endif //_HKA_TYPES_H_



