/***************************************************************************************************
* 版权信息：Copyright (c) 2010-2018, 杭州海康威视数字技术股份有限公司，保留所有权利
* 
* 文件名称：mvb_types.h
* 
* 摘    要：接口数据类型定义
* 
* 当前版本：0.7.0
* 作    者：邓志辉
* 日    期：2018年10月12日
* 备    注：1、加密类型增加深度学习
*
* 历史版本：0.6.0
* 作    者：邓志辉
* 日    期：2017年4月4日
* 备    注：1、增加多边形相关数据结构
*
* 历史版本：0.5.0
* 作    者：邓志辉
* 日    期：2017年1月12日
* 备    注：1、增加卡尺、blob相关数据结构
*
* 历史版本：0.4.0
* 作    者：邓志辉
* 日    期：2016年11月30日
* 备    注：1、MVBI_BOX修改为MVBI_BOX_F
*           2、MVB_CIRCLE_F和MVB_CIRCLE_I删除circleness成员
*           3、MVB_LINE_F和MVB_LINE_I删除straightness成员
* 历史版本：0.3.0
* 作    者：邓志辉
* 日    期：2016年1月23日
* 备    注：增加圆、直线、椭圆、模板匹配等结构体
*
* 历史版本：0.2.0
* 作    者：邓志辉
* 日    期：2016年1月19日
* 备    注：增加边缘类型、圆查找类型、直线查找类型、模板匹配信息等
*
* 历史版本：0.1.0
* 作    者：邹纯稳
* 日    期：2015年08月04日
* 备    注：初始版本
***************************************************************************************************/

#ifndef MVB_TYPES_H_
#define MVB_TYPES_H_

#include "hka_defs.h"

#ifdef __cplusplus        
extern "C" 
{
#endif

//插值算法种类 (interpolation)
typedef enum _MVBI_INTER_TYPE
{
    MVBI_INTER_TYPE_MIN = 1,
    MVBI_INTER_NN       = 1,
    MVBI_INTER_LINEAR   = 2,
    MVBI_INTER_CUBIC    = 4,
    MVBI_INTER_LANCZOS2 = 8,
    MVBI_INTER_LANCZOS3 = 16,
    MVBI_INTER_TYPE_MAX = 16
}MVBI_INTER_TYPE;

//范数类型 (normalizeType)
typedef enum _MVBI_NORM_TYPE
{
    MVBI_NORM_TYPE_MIN = 0,
    MVBI_NORM_C        = 0,
    MVBI_NORM_L1       = 1,
    MVBI_NORM_L2       = 2,
    MVBI_NORM_TYPE_MAX = 2
}MVBI_NORM_TYPE;

//bayer数据类型 (bayerType)
typedef enum _MVBI_BAYER_TYPE
{
    MVBI_BAYER_TYPE_MIN = 0,
    MVBI_BAYER_GRBG     = 0,
    MVBI_BAYER_GBRG     = 1,
    MVBI_BAYER_RGGB     = 2,
    MVBI_BAYER_BGGR     = 3,
    MVBI_BAYER_TYPE_MAX = 3
}MVBI_BAYER_TYPE;

//扩散方程 (diffusionMode)
typedef enum _MVBI_DIFFUSION_TYPE
{
    MVBI_DIFFUSION_TYPE_MIN = 1, 
    MVBI_DIFFUSION_1        = 1,
    MVBI_DIFFUSION_2        = 2,
    MVBI_DIFFUSION_3        = 3,
    MVBI_DIFFUSION_TYPE_MAX = 3
}MVBI_DIFFUSION_TYPE;

// 方向类型 (directionType)
typedef enum _MVBI_DIRECT_TYPE
{
    MVBI_DIRECT_TYPE_MIN = 0, 
    MVBI_DIRECT_0        = 0,
    MVBI_DIRECT_45       = 1,
    MVBI_DIRECT_90       = 2,
    MVBI_DIRECT_135      = 3,
    MVBI_DIRECT_TYPE_MAX = 3
}MVBI_DIRECT_TYPE;

//加权中值滤波Mask类型 (maskType)
typedef enum _MVBI_MASKTYPE_TYPE
{
    MVBI_MASKTYPE_TYPE_MIN = 0,
    MVBI_MASKTYPE_GAUSS    = 0,
    MVBI_MASKTYPE_INNER    = 1,
    MVBI_MASKTYPE_TYPE_MAX = 1
}MVBI_MASKTYPE_TYPE;

//在空域内平滑图像来抑制噪声函数像素值替换类型 (replacementMode)
typedef enum _MVBI_REPLACEMENT_TYPE
{
    MVBI_REPLACEMENT_TYPE_MIN = 0, 
    MVBI_REPLACEMENT_NEXT     = 0,
    MVBI_REPLACEMENT_MEAN     = 1,
    MVBI_REPLACEMENT_MEDIAN   = 2,
    MVBI_REPLACEMENT_TYPE_MAX = 2
}MVBI_REPLACEMENT_TYPE;

//连通类型
typedef enum _MVBI_CONNECTIVITY
{
    MVBI_CONNECTIVITY_MIN = 4,
    MVBI_CONNECTIVITY_4   = 4,      // 4连通  4-邻域
    MVBI_CONNECTIVITY_6   = 6,      // 6连通  6-邻域
    MVBI_CONNECTIVITY_8   = 8,      // 8连通  8-邻域
    MVBI_CONNECTIVITY_MAX = 8
} MVBI_CONNECTIVITY;

//连通域集排序类型：_MVBI_SortDomainArray函数使用
typedef enum _MVBI_REG_DOMAIN_ARRAY_SORT_TYPE
{
    MVBI_REG_SORT_TYPE_MIN  = 0,
    MVBI_REG_SORT_TYPE_AREA = 0,  //按面积排序
    MVBI_REG_SORT_TYPE_YMIN = 1,  //按矩形盒上边缘排序
    MVBI_REG_SORT_TYPE_YMAX = 2,  //按矩形盒下边缘排序
    MVBI_REG_SORT_TYPE_XMIN = 3,  //按矩形盒左边缘排序
    MVBI_REG_SORT_TYPE_XMAX = 4,  //按矩形盒右边缘排序
    MVBI_REG_SORT_TYPE_MAX  = 4
}MVBI_REG_DOMAIN_ARRAY_SORT_TYPE;

// 距离类型
typedef enum _MVBI_DIST_TYPE
{
    MVBI_DIST_TYPE_MIN       = 0, 
    MVBI_DIST_TYPE_BLOCK     = 0,	  // 街区距离
    MVBI_DIST_TYPE_CHESS     = 1,	  // 棋盘距离
    MVBI_DIST_TYPE_EUCLIDEAN = 2, 	  // 欧式距离
    MVBI_DIST_TYPE_MAX       = 2
}MVBI_DIST_TYPE;

// 结构元素数据类型
typedef enum _MVBI_MORPH_STRUCTURE
{
    MVBI_MORPH_STRUCTURE_MIN     = 0x0000,  // 最小类型
    MVBI_MORPH_STRUCTURE_RECT    = 0x0000,  // 矩形
    MVBI_MORPH_STRUCTURE_ELLIPSE = 0x0001,  // 椭圆
    MVBI_MORPH_STRUCTURE_CROSS   = 0x0002,  // 十字形
    MVBI_MORPH_STRUCTURE_CUSTOM  = 0x0003,  // 枚举(自定义)
    MVBI_MORPH_STRUCTURE_MAX     = 0x0003  // 最大类型

}MVBI_MORPH_STRUCTURE;

// 帧平均模式
typedef enum _MVBI_FRAME_AVG_TYPE
{
    MVBI_FRAME_AVG_STANDARD    = 0, // 标准模式
    MVBI_FRAME_AVG_ROLLING_AVG = 1, // Rolling卷帘平均模式

}MVBI_FRAME_AVG_TYPE;

// 边缘极性类型
typedef enum _MVBI_EDGE_POLARITY
{
    MVBI_EDGE_POLARITY_MIN            = 0x0001,
	MVBI_EDGE_POLARITY_DARK_TO_BRIGHT = 0x0001, // 由黑到白边
	MVBI_EDGE_POLARITY_BRIGHT_TO_DARK = 0x0002, // 由白到黑边
	MVBI_EDGE_POLARITY_BOTH           = 0x0003, // 两种类型边
    MVBI_EDGE_POLARITY_MAX            = 0x0003
}MVBI_EDGE_POLARITY;

// 边缘模型
typedef enum _MVBI_EDGE_MODE
{
    MVBI_EDGE_MODE_MIN         = 0x0001,
    MVBI_EDGE_MODE_SIGNLE_EDGE = 0x0001, // 单个边缘
    MVBI_EDGE_MODE_EDGE_PAIR   = 0x0002, // 边缘对
    MVBI_EDGE_MODE_MAX         = 0x0002
}MVBI_EDGE_MODE;

// 边缘评分模型
typedef enum _MVBI_EDGE_SCORE_MODE
{
    MVBI_EDGE_SCORE_MODE_MIN         = 0x0001,
    MVBI_EDGE_SCORE_MODE_CONTRAST    = 0x0001, // 对比度评分
    MVBI_EDGE_SCORE_MODE_POSITION    = 0x0002, // 位置评分
    MVBI_EDGE_SCORE_MODE_SIZE        = 0x0003, // 边缘对间距评分(仅边缘对使用)
    MVBI_EDGE_SCORE_MODE_STRADDLE    = 0x0004, // 边缘对鞍点评分(仅边缘对使用)
    MVBI_EDGE_SCORE_MODE_MAX         = 0x0004
}MVBI_EDGE_SCORE_MODE;

//卡尺投影类型
typedef enum _MVBI_CALIPER_PROJECTION_TYPES
{
    MVBI_CALIPER_PROJECTION_TYPE_MIN  = 0x0000,
    MVBI_CALIPER_PROJECTION_TO_HEIGHT = 0x0000, // 投向高(横向投影)
    MVBI_CALIPER_PROJECTION_TO_WIDTH  = 0x0001, // 投向宽(纵向投影)
    MVBI_CALIPER_PROJECTION_TO_RADIUS = 0x0002, // 投向半径(环向投影)
    MVBI_CALIPER_PROJECTION_TO_ARC    = 0x0003, // 投向圆弧(径向投影)
    MVBI_CALIPER_PROJECTION_TYPE_MAX  = 0x0003

}MVBI_CALIPER_PROJECTION_TYPES;

//卡尺对比度阈值类型
typedef enum _MVBI_CALIPER_THRESHOLD_TYPES
{
    MVBI_CALIPER_THRESHOLD_TYPE_MIN  = 0x0000,
    MVBI_CALIPER_THRESHOLD_ABSOLUTE  = 0x0000, // 绝对阈值（固定数值）
    MVBI_CALIPER_THRESHOLD_RELATIVE  = 0x0001, // 相对阈值（相对百分比）
    MVBI_CALIPER_THRESHOLD_TYPE_MAX  = 0x0001

}MVBI_CALIPER_THRESHOLD_TYPES;

//圆查找类型
typedef enum _MVBI_CIRCLE_FIND_MODES
{
    MVBI_CIRCLE_FIND_MODES_MIN = 0x0001, // 最小圆查找类型
    MVBI_CIRCLE_FIND_BEST      = 0x0001, // 查找最佳圆
    MVBI_CIRCLE_FIND_LARGEST   = 0x0002, // 查找最大的圆
    MVBI_CIRCLE_FIND_SMALLEST  = 0x0003, // 查找最小的圆
    MVBI_CIRCLE_FIND_MODES_MAX = 0x0003  // 最大圆查找类型
}MVBI_CIRCLE_FIND_MODES;

//圆扫描方向
typedef enum _MVBI_CIRCLE_SCAN_TYPES
{
    MVBI_CIRCLE_SCAN_TYPES_MIN       = 0x0001, // 最小圆扫描方向
    MVBI_CIRCLE_SCAN_INNER_TO_OUTER  = 0x0001, // 由内向外
    MVBI_CIRCLE_SCAN_OUTER_TO_INNER  = 0x0002, // 由外向内
    MVBI_CIRCLE_SCAN_TYPES_MAX       = 0x0002  // 最大圆扫描方向
}MVBI_CIRCLE_SCAN_TYPES;

//直线查找类型
typedef enum _MVBI_LINE_FIND_MODES
{
    MVBI_LINE_FIND_MODES_MIN = 0x0001,
    MVBI_LINE_FIND_BEST      = 0x0001, // 查找最佳直线
    MVBI_LINE_FIND_FIRST     = 0x0002, // 查找第一条直线
    MVBI_LINE_FIND_LAST      = 0x0003, // 查找最后一条直线
    MVBI_LINE_FIND_MODES_MAX = 0x0003
}MVBI_LINE_FIND_MODES;

//边缘查找类型
typedef enum _MVBI_EDGE_FIND_MODES
{
    MVBI_EDGE_FIND_MODES_MIN = 0x0001,
    MVBI_EDGE_FIND_BEST      = 0x0001, // 查找最强边缘
    MVBI_EDGE_FIND_FIRST     = 0x0002, // 查找第一个边缘
    MVBI_EDGE_FIND_LAST      = 0x0003, // 查找最后一个边缘
    MVBI_EDGE_FIND_ALL       = 0x0004, // 查找所有边缘
    MVBI_EDGE_FIND_MODES_MAX = 0x0004
}MVBI_EDGE_FIND_MODES;

//边缘对查找类型
typedef enum _MVBI_EDGE_PAIR_FIND_MODES
{
    MVBI_EDGE_PAIR_FIND_MODES_MIN = 0x0001,
    MVBI_EDGE_PAIR_FIND_WIDEST    = 0x0001, // 查找最宽边缘对
    MVBI_EDGE_PAIR_FIND_NARROWEST = 0x0002, // 查找最窄边缘对
    MVBI_EDGE_PAIR_FIND_STRONGEST = 0x0003, // 查找最强边缘对
    MVBI_EDGE_PAIR_FIND_WORST     = 0x0004, // 查找最弱边缘对
    MVBI_EDGE_PAIR_FIND_FIRST     = 0x0005, // 查找第一个边缘对
    MVBI_EDGE_PAIR_FIND_LAST      = 0x0006, // 查找最后一个边缘对
    MVBI_EDGE_PAIR_FIND_NEAREST   = 0x0007, // 查找最接近边缘对
    MVBI_EDGE_PAIR_FIND_FARTHEST  = 0x0008, // 查找最不接近边缘对
    MVBI_EDGE_PAIR_FIND_ALL       = 0x0009, // 查找所有边缘对
    MVBI_EDGE_PAIR_FIND_MODES_MAX = 0x0009
}MVBI_PAIR_FIND_FIND_MODES;

// 直线查找方向
typedef enum _MVBI_LINE_FIND_ORIENT
{
    MVBI_LINE_FIND_ORIENT_MIN           = 0x0001,
    MVBI_LINE_FIND_ORIENT_UP_TO_DOWN    = 0x0001,  //从上到下搜索
    MVBI_LINE_FIND_ORIENT_LEFT_TO_RIGHT = 0x0002,  //从左到右搜索
    MVBI_LINE_FIND_ORIENT_DOWN_TO_UP    = 0x0003,  //从下到上搜索
    MVBI_LINE_FIND_ORIENT_RIGHT_TO_LEFT = 0x0004,  //从右到左搜索
    MVBI_LINE_FIND_ORIENT_MAX           = 0x0004
}MVBI_LINE_FIND_ORIENT;

// 边缘查找方向
typedef enum _MVBI_EDGE_FIND_ORIENT
{
    MVBI_EDGE_FIND_ORIENT_MIN             = 0x0001,
    MVBI_EDGE_FIND_ORIENT_UP_TO_DOWN      = 0x0001, //从上到下搜索
    MVBI_EDGE_FIND_ORIENT_LEFT_TO_RIGHT   = 0x0002, //从左到右搜索
    MVBI_EDGE_FIND_ORIENT_DOWN_TO_UP      = 0x0003, //从下到上搜索
    MVBI_EDGE_FIND_ORIENT_RIGHT_TO_LEFT   = 0x0004, //从右到左搜索
    MVBI_EDGE_FIND_ORIENT_INNER_TO_OUTER  = 0x0005, //由内向外搜索
    MVBI_EDGE_FIND_ORIENT_OUTER_TO_INNER  = 0x0006, //由外向内搜索
    MVBI_EDGE_FIND_ORIENT_CLOCKWISE       = 0x0007, //顺时针搜索
    MVBI_EDGE_FIND_ORIENT_ANCLOCKWISE     = 0x0008, //逆时针搜索
    MVBI_EDGE_FIND_ORIENT_MAX             = 0x0008
}MVBI_EDGE_FIND_ORIENT;


//边缘计分方式为前三种，边缘对计分方式全部可用
typedef enum _MVBI_CALIPER_SCORE_TYPE
{
    MVBI_CALIPER_SCORE_TYPES_MIN           = 0x00000001, // 卡尺边缘对计分类型最小编号
    MVBI_CALIPER_SCORE_CONSTRAST           = 0x00000001, // 对比度评分，按边缘对比度或边对对比度均值计分
    MVBI_CALIPER_SCORE_POSITION            = 0x00000002, // 位置评分，按边缘或边对的中心线相对BOX中心线的绝对垂直距离
    MVBI_CALIPER_SCORE_POSITION_NEG        = 0x00000004, // 位置评分，按边缘或边对的中心线相对BOX中心线的垂直位置差（可正可负）
    MVBI_CALIPER_SCORE_POSITION_NORM       = 0x00000008, // 位置评分，按边对的中心线相对BOX中心线的绝对垂直归一化距离，归一化分母为边线对宽度（输入参数edge_pair_width）
    MVBI_CALIPER_SCORE_POSITION_NORM_NEG   = 0x00000010, // 位置评分，按边对的中心线相对BOX中心线的垂直归一化位置差（可正可负），归一化分母为边线对宽度
    MVBI_CALIPER_SCORE_SIZE_DIFF_NORM      = 0x00000020, // 边缘对间距评分，按|(边对距离-边线对宽度)/边线对宽度|，单边计分方式
    MVBI_CALIPER_SCORE_SIZE_DIFF_NORM_ASYM = 0x00000040, // 边缘对间距评分，按(边对距离-边线对宽度)/边线对宽度，双边计分方式
    MVBI_CALIPER_SCORE_SIZE_NORM           = 0x00000080, // 边缘对间距评分，按边对距离/边线对宽度
    MVBI_CALIPER_SCORE_STRADDLE            = 0x00000100, // 边缘对鞍点评分，按跨度计分，即两条边线在box中心线两边
    MVBI_CALIPER_SCORE_GRAY                = 0x00000200, // 灰度计分，按边缘灰度或边对灰度均值计分
    MVBI_CALIPER_SCORE_TYPES_MAX           = 0x000003FF, // 卡尺边缘对计分最大编号

}MVBI_CALIPER_SCORE_TYPE;

// 模板模型类型
typedef enum _MVBI_PAT_MODEL_TYPES
{
    MVBI_PAT_MODEL_TYPE_MIN   = 0x0001, // 最小模板模型类型
    MVBI_PAT_MODEL_TYPE_GRAY  = 0x0002, // 灰度模板模型
    MVBI_PAT_MODEL_TYPE_EDGE  = 0x0003, // 边缘模板模型
    MVBI_PAT_MODEL_TYPE_PROBE = 0x0004, // 探针模板模型
    MVBI_PAT_MODEL_TYPE_MAX   = 0x0004  // 最大模板模型类型
}MVBI_PAT_MODEL_TYPES;

// blob排序类型(MVBI_BlobSort/_MVBI_BlobSort使用)
typedef enum _MVBI_BLOBSORT_TYPE
{
    MVBI_BLOB_SORT_TYPE_MIN           = 0x00000001, // blob排序方式最小值
    MVBI_BLOB_SORT_TYPE_BY_AREA       = 0x00000001, // 按面积从大到小进行排序
    MVBI_BLOB_SORT_TYPE_UP_TO_DOWN    = 0x00000002, // 从上到下排序 按Y
    MVBI_BLOB_SORT_TYPE_LEFT_TO_RIGHT = 0x00000003, // 从左到右排序 按X
    MVBI_BLOB_SORT_TYPE_TWO_DIMENSION = 0x00000004, // 二维排序
    MVBI_BLOB_SORT_TYPE_ANGLE_ASCEND  = 0x00000005, // box角度升序
    MVBI_BLOB_SORT_TYPE_NO_SORT       = 0x00000006, // 放弃排序
    MVBI_BLOB_SORT_TYPE_MAX           = 0x00000006, // blob排序方式最大值

}MVBI_BLOBSORT_TYPE;

// blob排序特征
typedef enum _MVBI_BLOBSORT_FEATURE
{
    MVBI_BLOB_SORT_FEATURE_MIN                  = 0x00000001, // blob排序特征序号最小值
    MVBI_BLOB_SORT_FEATURE_AREA                 = 0x00000001, // 面积
    MVBI_BLOB_SORT_FEATURE_PERIMETER            = 0x00000002, // 周长
    MVBI_BLOB_SORT_FEATURE_CIRCULARITY          = 0x00000003, // 圆形度
    MVBI_BLOB_SORT_FEATURE_RECTANGULARITY       = 0x00000004, // 矩形度
    MVBI_BLOB_SORT_FEATURE_CENTROID_X           = 0x00000005, // 连通域中心x
    MVBI_BLOB_SORT_FEATURE_CENTROID_Y           = 0x00000006, // 连通域中心y
    MVBI_BLOB_SORT_FEATURE_BOX_ANGLE            = 0x00000007, // box角度
    MVBI_BLOB_SORT_FEATURE_BOX_LONG_AXIS        = 0x00000008, // box长轴（宽）
    MVBI_BLOB_SORT_FEATURE_BOX_SHORT_AXIS       = 0x00000009, // box短轴(高)
    MVBI_BLOB_SORT_FEATURE_RECT_X               = 0x0000000A, // rect.x
    MVBI_BLOB_SORT_FEATURE_RECT_Y               = 0x0000000B, // rect.y
    MVBI_BLOB_SORT_FEATURE_PRINCIPAL_AXIS_ANGLE = 0x0000000C, // 二阶中心距主轴角度
    MVBI_BLOB_SORT_FEATURE_AXIS_RATIO           = 0x0000000D, // 轴比：box短轴 / box长轴
    MVBI_BLOB_SORT_FEATURE_MAX                  = 0x0000000D, // blob排序特征序号最大值

}MVBI_BLOBSORT_FEATURE;

// blob排序方式
typedef enum _MVBI_BLOBSORT_MODE
{
    MVBI_BLOB_SORT_MODE_MIN          = 0x00000001, // blob排序方式最小值
    MVBI_BLOB_SORT_MODE_ASCEND       = 0x00000001, // 升序
    MVBI_BLOB_SORT_MODE_DESCEND      = 0x00000002, // 降序
    MVBI_BLOB_SORT_MODE_NO_SORT      = 0x00000003, // 放弃排序
    MVBI_BLOB_SORT_MODE_MAX          = 0x00000003, // blob排序方式最大值

}MVBI_BLOBSORT_MODE;


//使能标记，用来标记筛选因子
typedef enum _MVBI_BLOBSELECT_ENABLES
{
    MVBI_BLOBSELECT_ENABLE_MIN            = 0x00000000,  // 最小编号
    MVBI_BLOBSELECT_ENABLE_CLOSED         = 0x00000000,  // 使能关闭
    MVBI_BLOBSELECT_ENABLE_AREA           = 0x00000001,  // 面积使能
    MVBI_BLOBSELECT_ENABLE_PERIMETER      = 0x00000002,  // 轮廓长使能
    MVBI_BLOBSELECT_ENABLE_SHORTAXIS      = 0x00000004,  // 短轴使能
    MVBI_BLOBSELECT_ENABLE_LONGAXIS       = 0x00000008,  // 长轴使能
    MVBI_BLOBSELECT_ENABLE_CIRCULARITY    = 0x00000010,  // 圆形度使能
    MVBI_BLOBSELECT_ENABLE_RECTANGULARITY = 0x00000020,  // 矩形度使能
    MVBI_BLOBSELECT_ENABLE_CENTRABIAS     = 0x00000040,  // 质心相对于矩形中心的偏移使能
    MVBI_BLOBSELECT_ENABLE_AXIS_RATIO     = 0x00000080,  // 轴比使能(短轴/长轴)
    MVBI_BLOBSELECT_ENABLE_MAX            = 0x000000FF,  // 最大编号

}MVBI_BLOBSELECT_ENABLES;

//blob特征有效标记
typedef enum _MVBI_BLOB_VALID_FEATURE_FLAG
{
    MVBI_BLOB_VALID_MIN            = 0x00000001,  // 最小编号
    MVBI_BLOB_VALID_AREA           = 0x00000001,  // 面积有效
    MVBI_BLOB_VALID_RECT           = 0x00000002,  // 包围盒有效
    MVBI_BLOB_VALID_CENTROID       = 0x00000004,  // 连通域中心（质心）有效
    MVBI_BLOB_VALID_PERIMETER      = 0x00000008,  // 轮廓长有效
    MVBI_BLOB_VALID_CIRCULARITY    = 0x00000010,  // 圆形度有效
    MVBI_BLOB_VALID_BOX            = 0x00000020,  // 最小面积外接矩有效
    MVBI_BLOB_VALID_SHORTAXIS      = 0x00000040,  // 短轴有效
    MVBI_BLOB_VALID_LONGAXIS       = 0x00000080,  // 长轴有效
    MVBI_BLOB_VALID_ANGLE          = 0x00000100,  // 角度有效
    MVBI_BLOB_VALID_RECTANGULARITY = 0x00000200,  // 矩形度有效
    MVBI_BLOB_VALID_CENTRABIAS     = 0x00000400,  // 质心相对于矩形中心的偏移有效
    MVBI_BLOB_VALID_AXIS_RATIO     = 0x00000800,  // 轴比（短轴 / 长轴）有效
    MVBI_BLOB_VALID_MAX            = 0x00000FFF,  // 最大编号

}MVBI_BLOB_VALID_FEATURE_FLAG;


//支持的ROI类型：掩膜生成模块内存计算接口MVBI_GenRoiMaskBufferSize_opt_pr使用
typedef enum _MVBI_GEN_ROI_MASK_TYPE
{
    MVBI_GEN_ROI_MASK_TYPE_MIN       = 0x0001, // 最小值
    MVBI_GEN_ROI_MASK_TYPE_RECT      = 0x0001, // 最小包围矩形
    MVBI_GEN_ROI_MASK_TYPE_BOX       = 0x0002, // 最小包围框
    MVBI_GEN_ROI_MASK_TYPE_CIRCLE    = 0x0004, // 圆
    MVBI_GEN_ROI_MASK_TYPE_ANNULUS   = 0x0008, // 圆环
    MVBI_GEN_ROI_MASK_TYPE_POLYGON_I = 0x0010, // 多边形
    MVBI_GEN_ROI_MASK_TYPE_MAX       = 0x001F, // 最大值

}MVBI_GEN_ROI_MASK_TYPE;

// 圆与圆的位置关系
typedef enum _MVB_CIRCLE_TO_CIRCLE_TYPES
{
    MVB_CIRCLE_TO_CIRCLE_TYPES_MIN = 0x00000001,
    MVB_CIRCLE_TO_CIRCLE_CONTAIN   = 0x00000001,     // 内含
    MVB_CIRCLE_TO_CIRCLE_INSCRIBE  = 0x00000002,     // 内切
    MVB_CIRCLE_TO_CIRCLE_INTERSECT = 0x00000003,     // 相交
    MVB_CIRCLE_TO_CIRCLE_EXCIRCLE  = 0x00000004,     // 外切
    MVB_CIRCLE_TO_CIRCLE_DEVIATION = 0x00000005,     // 外离
    MVB_CIRCLE_TO_CIRCLE_TYPES_MAX = 0x00000005,
}MVB_CIRCLE_TO_CIRCLE_TYPES;


// RGB转灰度处理的类型
typedef enum _MVBI_RGB_TO_GRAY_TYPE
{
    MVBI_RGB_TO_GRAY_TYPE_MIN            = 0x00000001,  // 最小处理类型
    MVBI_RGB_TO_GRAY_GENERAL_RATIO       = 0x00000001,  // 通用转换比例 0.299r + 0.587g + 0.114b
    MVBI_RGB_TO_GRAY_AVERAGE_RATIO       = 0x00000002,  // 平均转换比例 (r + g + b) / 3
    MVBI_RGB_TO_GRAY_MAX_CHANNEL_VALUE   = 0x00000003,  // 通道最大值 max(r, g, b)
    MVBI_RGB_TO_GRAY_MIN_CHANNEL_VALUE   = 0x00000004,  // 通道最小值 min(r, g, b)
    MVBI_RGB_TO_GRAY_TYPE_MAX            = 0x00000004,  // 最大处理类型

}MVBI_RGB_TO_GRAY_TYPE;

#define MVB_BINARY_TRUE  (0xff) // 二值图true
#define MVB_BINARY_FALSE (0)   // 二值图false

// 棋盘格
#define MVBI_CHESSBOARD_FLT_MAX       (1000000.0f) // 棋盘格之间的最大距离pixel^2
#define MVBI_CHESSBOARD_MAX_ERODENUM  (6)          // 最大腐蚀操作次数
#define MVBI_CHESSBOARD_WIDTH_MIN     (64)         // 支持最小图像宽
#define MVBI_CHESSBOARD_HEIGHT_MIN    (64)         // 支持最小图像高
#define MVBI_CHESSBOARD_PATTERN_WMIN  (4)          // 支持最小模板宽
#define MVBI_CHESSBOARD_PATTERN_HMIN  (4)          // 支持最小模板高
#define MVBI_CHESSBOARD_PATTERN_WMAX  (25)         // 支持最大模板宽
#define MVBI_CHESSBOARD_PATTERN_HMAX  (25)         // 支持最大模板高
#define MVBI_CHESSBOARD_BORDER        (8.0f)       // 角点离图像边缘地最小距离
#define MVBI_CHESSBOARD_NUM_MAX       (800)        // 支持最大方格个数
#define MVBI_CHESSBOARD_CORNUM_MAX    (3200)       // 支持最大方格角点个数
#define MVBI_CHESSBOARD_THRESH_GLOBAL (1)          // 局部阈值
#define MVBI_CHESSBOARD_THRESH_LOCAL  (0)          // 全局阈值
#define MVBI_CHESSBOARD_MIN_WINWIDTH  (2)        // 亚像素角点提取最小窗口一半宽度
#define MVBI_CHESSBOARD_MIN_WINHEIGHT (2)        // 亚像素角点提取最小窗口一半高度
#define MVBI_CHESSBOARD_MAX_WINWIDTH  (50)       // 亚像素角点提取最大窗口一半宽度
#define MVBI_CHESSBOARD_MAX_WINHEIGHT (50)       // 亚像素角点提取最大窗口一半高度

#define  MVB_SWAP(TYPE, a, b) \
{                             \
    TYPE c = a;               \
    a = b;                    \
    b = c;                    \
    }

// 位置补正模式
typedef enum _MVBI_POS_FIX_MODE
{
    MVBI_POS_FIX_MODE_MIN       = 0x00000001,  // 最小编号
    MVBI_POS_FIX_MODE_NONE      = 0x00000001,  // 不补正
    MVBI_POS_FIX_MODE_HORI      = 0x00000002,  // 水平补正
    MVBI_POS_FIX_MODE_VERT      = 0x00000003,  // 垂直补正
    MVBI_POS_FIX_MODE_HV        = 0x00000004,  // 水平垂直补正
    MVBI_POS_FIX_MODE_HVA       = 0x00000005,  // 水平垂直角度补正
	MVBI_POS_FIX_MODE_HVAS      = 0x00000006,  // 水平垂直角度尺度补正
    MVBI_POS_FIX_MODE_MAX       = 0x00000006,  // 最大编号
}MVBI_POS_FIX_MODE;

// 二值化分割类型
typedef enum _MVBI_LINE_SCAN_SEGMENT_TYPE
{
    MVBI_LINE_SCAN_SEGMENT_BRIGHT  = 0x00000001,    // 分割相比背景亮的对象
    MVBI_LINE_SCAN_SEGMENT_DARK    = 0x00000002,    // 分割相比背景暗的对象

}MVBI_LINE_SCAN_SEGMENT_TYPE;

// 线扫描方式类型
typedef enum _MVBI_LINE_SCAN_MODE_TYPE
{
    MVBI_LINE_SCAN_HORIZONTAL_MODE          = 0x00000001,    // 水平方向线扫描，适合分割垂直方向的对象
    MVBI_LINE_SCAN_VERTICAL_MODE            = 0x00000002,    // 垂直方向线扫描，适合分割水平方向的对象
    MVBI_LINE_SCAN_HORIZONTAL_VERTICAL_MODE = 0x00000003,    // 水平加垂直方向线扫描

}MVBI_LINE_SCAN_MODE_TYPE;

// 回归函数(regression function)
typedef enum _MVB_REGRESSION_FUN
{
    MVB_REGRESSION_FUN_LEAST_SQUARE = 1, // 最小二乘
    MVB_REGRESSION_FUN_HUBER        = 2, // huber
    MVB_REGRESSION_FUN_TUKEY        = 3, // tukey
}MVB_REGRESSION_FUN;

//基于回归估计的几何拟合初始化类型
typedef enum _MVBI_GEOFIT_INIT_TYPE
{
    MVBI_GEOFIT_INIT_TYPE_MIN           = 0x0001,
    MVBI_GEOFIT_INIT_TYPE_LEAST_SQUARE  = 0x0001,  // 一次全局最小二乘
    MVBI_GEOFIT_INIT_TYPE_LS_EXHAUSTION = 0x0002,  // 穷举局部最小二乘，取最佳
    MVBI_GEOFIT_INIT_TYPE_OUTSIDE       = 0x0003,  // 外部传入
    MVBI_GEOFIT_INIT_TYPE_MAX           = 0x0003
}MVBI_GEOFIT_INIT_TYPE;

// 缺陷过滤类型
typedef enum _MVBI_DEFECT_FILTER_TYPE
{
    MVBI_DEFECT_FILTER_TYPE_NONE  = 0, // 不进行过滤
    MVBI_DEFECT_FILTER_TYPE_INNER = 1, // 过滤右边/下边，内部的缺陷,
    MVBI_DEFECT_FILTER_TYPE_OUTER = 2, // 过滤左边/上边,外部的缺陷,
    
}MVBI_DEFECT_FILTER_TYPE;

// 缺陷排序类型
typedef enum _MVBI_DEFECT_SORT_TYPE
{
    MVBI_DEFECT_SORT_BY_SIZE = 1, // 按照尺寸进行排序
    MVBI_DEFECT_SORT_BY_POS  = 2, // 按照位置进行排序
    MVBI_DEFECT_SORT_BY_AREA = 3, // 按照面积进行排序
}MVBI_DEFECT_SORT_TYPE;

// 任意方向矩形结构体
/*
*         1.外接矩形角度范围[-pi/2，pi/2]，表示矩形主轴方向与水平x轴的夹角.
*         2.矩形的宽度为长轴，高度为短轴.
*         3.此处的最小外接矩形是将像素点按点处理，即[1,1]的外接矩形宽度是1.
*           求解时矩形度时，调用此函数得到width、height后，需各加sqrt(2)用于近似.
*           实际宽度的范围是[width+1~width+sqrt(2)].
*/
typedef struct _MVBI_BOX_F
{
    HKA_F32 center_x;           // 中心点列坐标
    HKA_F32 center_y;           // 中心点行坐标
    HKA_F32 width;              // 矩形宽度。宽度为长半轴
    HKA_F32 height;             // 矩形高度。高度为短半轴
    HKA_F32 angle;              // 矩形角度。
} MVBI_BOX_F;

typedef struct _MVBI_BOX_I
{
    HKA_S32 center_x;           // 中心点列坐标
    HKA_S32 center_y;           // 中心点行坐标
    HKA_S32 width;              // 矩形宽度。宽度为长半轴
    HKA_S32 height;             // 矩形高度。高度为短半轴
    HKA_F32 angle;              // 矩形角度。
} MVBI_BOX_I;

typedef MVBI_BOX_F MVBI_BOX;

// 基于像素点的轮廓
typedef struct _MVBI_CONTOUR_32F
{
    HKA_POINT_F       *data;     // 像素点内存
    HKA_S32            count;    // 轮廓中所拥有的像素个数  

}MVBI_CONTOUR_F;

// 连通域轮廓
typedef struct _MVBI_CONTOUR_S
{
    HKA_POINT_S *point;     // 外轮廓点集
    HKA_S32      point_num; // 轮廓点数

}MVBI_CONTOUR_S;

// 团块特征
typedef struct _MVBI_BLOB_PROP
{
    MVBI_BOX_F  box;
    HKA_POINT_F centroid;
    HKA_S32     area;
}MVBI_BLOB_PROP;

//单个BLOB信息组成
typedef struct _MVBI_BLOB_PROPS
{
    HKA_F32        area;               // 面积
    HKA_RECT_I     rect;               // 该连通域包围盒
    HKA_POINT_F    centroid;           // 连通域中心（质心）

    HKA_F32        perimeter;          // 周长
    HKA_F32        circularity;        // 圆形度

    MVBI_BOX_F     box;                // 最小面积外接矩
    HKA_F32        shortaxis;          // 短轴长度
    HKA_F32        longaxis;           // 长轴长度
    HKA_F32        axis_ratio;         // 轴比（短轴/长轴）
    HKA_F32        rectangularity;     // 矩形度

    HKA_F32        centra_bias;        // 质心相对于外接矩中心的偏移值

    HKA_F32        angle;              // 角度(二阶中心距主轴角度)

    HKA_F32        score;              // 分数

    HKA_VOID      *domain;             // 该连通域句柄
    HKA_S32        domain_index;       // 连通域集中该blob的位置索引号（0,1,2,3,4,…）
    MVBI_CONTOUR_S domain_contour;     // 单连通域轮廓

    HKA_S32        label_id;           // 标签值，即当前blob的灰度值

}MVBI_BLOB_PROPS;

// 卡尺单个边缘检测结果信息
typedef struct _MVBI_CALIPER_INFO
{
    HKA_POINT_F edge_point;   // 检测边线中心点坐标
    HKA_F32     bias;         // 边线相对box中心线相对距离（可正可负）
    HKA_S32     polarity;     // 边线极性：1：黑到白的边线，2：白到黑的边线
    HKA_F32     score;        // 得分
}MVBI_CALIPER_INFO;

// 卡尺检测边缘信息（边缘对中使用）
typedef struct _MVBI_CALIPER_EDGE
{
    HKA_POINT_F edge_point;   // 检测边线中心点坐标
    HKA_F32     bias;         // 边线相对box中心线相对距离（可正可负）
    HKA_S32     polarity;     // 边线极性：1：黑到白的边线，2：白到黑的边线
}MVBI_CALIPER_EDGE;

// 卡尺检测边线对信息输出
typedef struct _MVBI_CALIPER_PAIR_INFO
{
    MVBI_CALIPER_EDGE caliper[2]; // 边缘0与边缘1信息
    HKA_POINT_F       centre;     // 边缘对中心点
    HKA_F32           position;   // 边缘对位置（边缘对中心（几何平均）相对区域中心的距离，可正可负）
    HKA_F32           dist;       // 边缘对间距
    HKA_F32           score;      // 得分
}MVBI_CALIPER_PAIR_INFO;

// 模板匹配信息
typedef struct _MVBI_PAT_MATCH_INFO
{
    MVBI_BOX_F     match_box;    // 模板匹配区域包围框
    HKA_POINT_F    match_point;  // 模板匹配点
    HKA_F32        match_scale;  // 模板匹配尺度
    HKA_F32        match_score;  // 相似分数
}MVBI_PAT_MATCH_INFO;

// 圆系数(整型)
typedef struct _MVB_CIRCLE_I
{
    HKA_POINT_I center;       // 圆中心点
    HKA_F32     radius;       // 圆半径
}MVB_CIRCLE_I;

// 圆系数(浮点型)
typedef struct _MVB_CIRCLE_F
{
    HKA_POINT_F center;        // 圆中心点
    HKA_F32     radius;        // 圆半径
}MVB_CIRCLE_F;

// 圆弧(浮点型)
typedef struct _MVB_ARC_F
{
    HKA_POINT_F center;        // 圆中心点
    HKA_F32     radius;        // 圆半径
    HKA_F32     start_angle;   // 起始角度
    HKA_F32     end_angle;     // 终止角度
}MVB_ARC_F;

//直线的系数
typedef struct _MVB_LINE_COE_
{
    HKA_F32 a;
    HKA_F32 b;
    HKA_F32 c;
}MVB_LINE_COE;

// 直线系数(整型)
typedef struct _MVB_LINE_F
{
    HKA_POINT_F point_start;   // 直线起点
    HKA_POINT_F point_end;     // 直线终点
    HKA_F32     angle;         // 直线角度
}MVB_LINE_F;

// 直线系数(浮点型)
typedef struct _MVB_LINE_I
{
    HKA_POINT_I point_start;   // 直线起点
    HKA_POINT_I point_end;     // 直线终点
    HKA_F32     angle;         // 直线角度
}MVB_LINE_I;

// 椭圆参数(浮点型)
typedef struct _MVB_ELLIPSE_F
{
    HKA_POINT_F center;        // 椭圆中心
    HKA_POINT_F focus1;        // 椭圆焦点1
    HKA_POINT_F focus2;        // 椭圆焦点2
    HKA_F32     major_axis;    // 椭圆主轴长度
    HKA_F32     minor_axis;    // 椭圆次轴长度
    HKA_F32     angle;         // 椭圆角度
}MVB_ELLIPSE_F;

//椭圆的系数
typedef struct _MVB_ELLIPSE_COE_F
{
    HKA_F32 a;
    HKA_F32 b;
    HKA_F32 c;
    HKA_F32 d;
    HKA_F32 e;
    HKA_F32 f;
}MVB_ELLIPSE_COE_F;

// rhomboid 平行四边形结构体
typedef struct _MVBI_RHOMBOID_F 
{
    HKA_F32 center_x;            // 中心点列坐标
    HKA_F32 center_y;            // 中心点行坐标
    HKA_F32 width;               // 平行四边形宽向边长
    HKA_F32 height;              // 平行四边形高向边长
    HKA_F32 rotation;            // 旋转角度
    HKA_F32 skew;                // 倾斜角度
} MVBI_RHOMBOID_F;

typedef struct _MVBI_RHOMBOID_I 
{
    HKA_S32 center_x;            // 中心点列坐标
    HKA_S32 center_y;            // 中心点行坐标
    HKA_S32 width;               // 平行四边形宽向边长
    HKA_S32 height;              // 平行四边形高向边长
    HKA_F32 rotation;            // 旋转角度
    HKA_F32 skew;                // 倾斜角度
} MVBI_RHOMBOID_I;

// 角度方向
typedef enum _MVBI_ANGLE_DIR_TYPE
{
    MVBI_ANGLE_DIR_ANTI_CLOCKWISE = 1, // 逆时针
    MVBI_ANGLE_DIR_CLOCKWISE      = 2, // 顺时针

}MVBI_ANGLE_DIR_TYPE;

// 半径方向
typedef enum _MVBI_POLAR_RADIUS_DIR
{
    MVBI_POLAR_RADIUS_DIR_INNER_TO_OUTER = 1, // 从内往外
    MVBI_POLAR_RADIUS_DIR_OUTER_TO_INNER = 2, // 从外往内

}MVBI_POLAR_RADIUS_DIR;

// annulus（圆环）
typedef struct _MVBI_ANNULUS_I
{
    HKA_POINT_I center;        // 中心点
    HKA_S32     inner_radius;  // 内圆半径
    HKA_S32     outer_radius;  // 外圆半径
    HKA_F32     start_angle;   // 圆环起始角度
    HKA_F32     angle_extend;  // 圆环角度范围
}MVBI_ANNULUS_I;

// annulus
typedef struct _MVBI_ANNULUS_F
{
    HKA_POINT_F center;        // 中心点
    HKA_F32     inner_radius;  // 内圆半径
    HKA_F32     outer_radius;  // 外圆半径
    HKA_F32     start_angle;   // 圆环起始角度
    HKA_F32     angle_extend;  // 圆环角度范围
}MVBI_ANNULUS_F;

// 圆弧
typedef struct _MVBI_ARC
{
    HKA_POINT_F center;      // 圆弧中心点
    HKA_F32     radius;      // 圆弧半径
    HKA_F32     start_angle; // 圆弧起始角度
    HKA_F32     angle_extend; // 圆弧角度范围
}MVBI_ARC;

//多边形(短整型)
typedef struct _MVB_POLYGON_S
{
    HKA_S32       vertex_num;     //顶点数
    HKA_POINT_S  *vertex_points;  //顶点
}MVB_POLYGON_S;

//多边形(整型)
typedef struct _MVB_POLYGON_I
{
    HKA_S32       vertex_num;      //顶点数
    HKA_POINT_I  *vertex_points;   //顶点
}MVB_POLYGON_I;

//多边形(浮点型)
typedef struct _MVB_POLYGON_F
{
    HKA_S32       vertex_num;      //顶点数
    HKA_POINT_F  *vertex_points;   //顶点
}MVB_POLYGON_F;

// ROI基元
typedef union _MVB_ROI_LET
{
    HKA_RECT_I     roi_rect;    // 最小包围矩形
    MVBI_BOX_F     roi_box;     // 最小包围框
    MVB_CIRCLE_F   roi_circle;  // 圆
    MVBI_ANNULUS_F roi_annulus; // 圆环
    MVB_POLYGON_I  roi_polygon; // 多边形表示
}MVB_ROI_LET;

// ROI参数
typedef struct _MVB_ROI_PARAM
{
    MVB_ROI_LET  roi_let;       // ROI基元
    HKA_S32      type;          // ROI类型
}MVB_ROI_PARAM;

// ROI类型
typedef enum _MVB_ROI_TYPE
{
    MVB_ROI_TYPE_RECT      = 0x0000, // 最小包围矩形
    MVB_ROI_TYPE_BOX       = 0x0001, // 最小包围框
    MVB_ROI_TYPE_CIRCLE    = 0x0002, // 圆
    MVB_ROI_TYPE_ANNULUS   = 0x0003, // 圆环
    MVB_ROI_TYPE_POLYGON_I = 0x0004, // 多边形
    MVB_ROI_TYPE_NUM       = 0x0005,
}MVB_ROI_TYPE;

typedef struct _MVBI_EDGELET
{
    HKA_POINT_F position;   // 位置
    HKA_F32     angle;      // 方向
    HKA_F32     magnitude;  // 幅值
}MVBI_EDGELET;

// EdgeLet Chain（边缘点链）
typedef struct _MVBI_EDGELET_CHAIN
{
    MVBI_EDGELET *edgelets;        // 边缘点(EdgeLet)数组
    HKA_S32       edgelet_count;    // 边缘点个数
}MVBI_EDGELET_CHAIN;

// EdgeLet Chain Set（边缘点链）
typedef struct _MVBI_EDGELET_CHAIN_SET
{
    MVBI_EDGELET    *edgelets;           // 边缘点(EdgeLet)数组
    HKA_S32         *chain_start_index;  // 每个边缘点链(FeatureLet Chain)在边缘点(EdgeLet)数组的起始位置
    HKA_S32         *chain_length;       // 每个边缘点链(FeatureLet Chain)长度    
    HKA_S32         chain_count;         // 边缘点链个数
    HKA_S32         edgelet_count;       // 边缘点个数
    HKA_S32         edgelet_capacity;    // 最大边缘点个数
    HKA_S32         chain_capacity;      // 最大边缘点链个数
}MVBI_EDGELET_CHAIN_SET;

// FeatureLet（元特征）
typedef struct _MVBI_FEATURELET
{
    HKA_POINT_F position;   // 位置
    HKA_F32     angle;      // 方向
    HKA_F32     magnitude;  // 幅值/相对尺度因子
    HKA_F32     weight;     // 权重(表示重要程度，默认值1)
    HKA_S32     is_mod_180; // 方向范围为360还是180
        
}MVBI_FEATURELET;

// FeatureLet Chain（元特征链）
typedef struct _MVBI_FEATURELET_CHAIN
{
    MVBI_FEATURELET *featurelets;        // 元特征(FeatureLet)数组
    HKA_S32          feature_count;       // 元特征个数
}MVBI_FEATURELET_CHAIN;

// FeatureLet Chain Set（元特征链集合）
typedef struct _MVBI_FEATURELET_CHAIN_SET
{
    MVBI_FEATURELET *featurelets;        // 元特征(FeatureLet)数组
    HKA_S32         *chain_start_index;  // 每个元特征链(FeatureLet Chain)在元特征(FeatureLet)数组的起始位置
    HKA_S32         *chain_length;       // 每个元特征链(FeatureLet Chain)长度    
    HKA_S32         *cholse_chain;       // 每个元特征链(FeatureLet Chain)是开轮廓还是闭轮廓标签
    HKA_S32          chain_count;         // 元特征链个数
    HKA_S32          feature_count;       // 元特征个数
    HKA_S32          featurelet_capacity; // 最大元特征个数
    HKA_S32          chain_capacity;      // 最大元特征链个数
}MVBI_FEATURELET_CHAIN_SET;

// 形状
typedef union _MVBI_SHAPE
{
    MVB_LINE_F    line;
    MVB_CIRCLE_F  circle;
    MVB_ARC_F     arc;
    MVB_ELLIPSE_F ellipse;
    
}MVBI_SHAPE;

// 位置修正时的基准点
typedef struct _MVBI_FIDUCIAL_POSE
{
    HKA_POINT_F basis_point;     // 基准点
    HKA_F32     basis_angle;     // 基准角度
	HKA_F32     basis_scale_x;   // x方向尺度
	HKA_F32     basis_scale_y;   // y方向尺度
	HKA_S32     reserved[6];     // 保留字节

	//运算符 == 重载
	bool operator==(const _MVBI_FIDUCIAL_POSE &FixInfo)
	{
		return((basis_point.x == FixInfo.basis_point.x)
			&& (basis_point.y == FixInfo.basis_point.y)
			&& (basis_angle == FixInfo.basis_angle)
			&& (basis_scale_x == FixInfo.basis_scale_x)
			&& (basis_scale_y == FixInfo.basis_scale_y));
	}
}MVBI_FIDUCIAL_POSE;

//圆查找/拟合状态
typedef enum _MVBI_CIRCLE_STATUS
{
    MVBI_CIRCLE_STATUS_FAILURE = 0x0000,  // 查找/拟合失败
    MVBI_CIRCLE_STATUS_SUCCESS = 0x0001,  // 查找/拟合成功并输出圆结果
    MVBI_CIRCLE_STATUS_LIMITED = 0x0002,  // 查找/拟合“成功”但圆结果不满足参数要求，如半径限制

}MVBI_CIRCLE_STATUS;

//几何边缘点状态
typedef enum _MVBI_GEOEDGET_STATUS
{
    MVBI_GEOEDGET_STATUS_USED    = 0x0001,  // 查找成功并使用
    MVBI_GEOEDGET_STATUS_NO_USED = 0x0002,  // 查找成功，放弃使用
    MVBI_GEOEDGET_STATUS_NO_FIND = 0x0003   // 查找失败

}MVBI_GEOEDGET_STATUS;

// 几何边缘点信息
typedef struct _MVBI_GEOEDGE_INFO
{
    HKA_POINT_F edge_point;   // 边缘点
    HKA_F32     score;        // 边缘得分
    HKA_S32     polarity;     // 边缘极性
    HKA_F32     dist;         // 边缘距离
    HKA_S32     status;       // 边缘点查找状态
}MVBI_GEOEDGE_INFO; 

//几何边缘点对信息
typedef struct _MVBI_GEOEDGE_WIDTH_INFO
{
    HKA_POINT_F edge0_point;  // 边缘点0
    HKA_POINT_F edge1_point;  // 边缘点1
    HKA_F32     score;        // 边缘得分
    HKA_S32     polarity0;    // 边缘0极性
    HKA_S32     polarity1;    // 边缘1极性
    HKA_F32     dist;         // 边缘距离
    HKA_S32     status;       // 边缘点查找状态
}MVBI_GEOEDGE_WIDTH_INFO; 

//PARALLEL：几何边缘点信息列表
typedef struct _MVBI_GEOEDGE_INFO_LIST
{
    MVBI_GEOEDGE_INFO *edge_info; // 边缘点信息
    HKA_S32            edge_num;  // 边缘点个数
}MVBI_GEOEDGE_INFO_LIST; 

//多线查找（PARALLEL）中线条与边缘点信息
typedef struct _MVBI_PARALLEL_INFO
{
    MVB_LINE_F             line;           //直线段
    HKA_S32                line_idx;       //直线段序号索引
    HKA_S32                line_sts;       //直线段状态
    HKA_F32                line_fit_err;   //直线段拟合误差
    HKA_F32                line_intensity; //直线边缘强度，直线所在边缘越清晰，该值越大
    MVBI_GEOEDGE_INFO_LIST edge;           //直线段边缘点信息

}MVBI_PARALLEL_INFO;

//多线查找（PARALLEL）中线排序类型
typedef enum _MVBI_PARALLEL_SORT_TYPE
{
    MVBI_PARALLEL_SORT_TYPE_MIN          = 0x0001,
    MVBI_PARALLEL_SORT_NEAR_TO_FAR       = 0x0001, // 由近至远（即从左至右或从上至下）
    MVBI_PARALLEL_SORT_FAR_TO_NEAR       = 0x0002, // 由远至近（即从右至左或从下至上）
    MVBI_PARALLEL_SORT_ERROR_ASCEND      = 0x0003, // 拟合误差升序（由小到大）
    MVBI_PARALLEL_SORT_INTENSITY_DESCEND = 0x0004, // 边缘强度降序（由强至弱）
    MVBI_PARALLEL_SORT_TYPE_MAX          = 0x0004
}MVBI_PARALLEL_SORT_TYPE;

//多线查找（PARALLEL）类型
typedef enum _MVBI_PARALLEL_FIND_MODE
{
    MVBI_PARALLEL_FIND_TYPE_MIN  = 0x0001,
    MVBI_PARALLEL_FIND_FIRST     = 0x0001, // 第一条
    MVBI_PARALLEL_FIND_LAST      = 0x0002, // 最后一条
    MVBI_PARALLEL_FIND_STRONGEST = 0x0003, // 边缘最强
    MVBI_PARALLEL_FIND_INDEX     = 0x0004, // 指定序号（一条）
    MVBI_PARALLEL_FIND_ALL       = 0x0005, // 所有
    MVBI_PARALLEL_FIND_TYPE_MAX  = 0x0005
}MVBI_PARALLEL_FIND_MODE;

// 多线查找（MULTILINE）中的直线边缘极性
typedef enum _MVBI_MULTILINE_LINE_POLARITY
{
    MVBI_MULTILINE_LINE_POLARITY_MIN            = 0x0001,
    MVBI_MULTILINE_LINE_POLARITY_DARK_TO_BRIGHT = 0x0001, // 由黑到白
    MVBI_MULTILINE_LINE_POLARITY_BRIGHT_TO_DARK = 0x0002, // 由白到黑
    MVBI_MULTILINE_LINE_POLARITY_MIXED          = 0x0003, // 由黑到白 & 由白到黑(同一条线段中点集有两种极性点)
    MVBI_MULTILINE_LINE_POLARITY_EITHER         = 0x0004, // 由黑到白 | 由白到黑(同一条线段中点集有一种极性点)
    MVBI_MULTILINE_LINE_POLARITY_MAX            = 0x0004

}MVBI_MULTILINE_LINE_POLARITY;

//MULTILINE:直线拟合模式
typedef enum _MVBI_MULTILINE_FIT_MODE
{
    MVBI_MULTILINE_FIT_MODE_RANSAC    = 0x0001,  // RANSAC
    MVBI_MULTILINE_FIT_MODE_EXHAUST   = 0x0002,  // 穷举

}MVBI_MULTILINE_FIT_MODE;

//MULTILINE:边缘点信息
typedef struct _MVBI_MULTILINE_EDGE_INFO
{
    HKA_POINT_F edge_point;      // 边缘点
    HKA_S32     polarity;        // 边缘极性
    HKA_F32     magnitude;       // 梯度幅值
    HKA_F32     orientation;     // 梯度方向
    HKA_F32     dist;            // 边缘距离（可正负）
    HKA_S32     status;          // 边缘点状态
    HKA_S32     caliper_index;   // 投影区域索引
    HKA_S32     line_index;      // 所属线段索引
}MVBI_MULTILINE_EDGE_INFO;

//MULTILINE:多线查找中线条与边缘点信息
typedef struct _MVBI_MULTILINE_INFO
{
    MVB_LINE_F line;           // 当前直线段
    HKA_F32    line_fit_err;   // 当前直线段拟合误差
    HKA_F32    line_intensity; // 当前直线段对比度强度
    HKA_F32    coverage_score; // 覆盖率分数
    HKA_S32    inliers_num;    // 在群点数量
    HKA_S32    line_index;     // 线段索引

}MVBI_MULTILINE_INFO;

// 二维变换参数
typedef struct _MVBI_TRANSFORM_2D_PARAM
{
    HKA_F32 scale;  // 尺度
    HKA_F32 tx;     // x方向平移
    HKA_F32 ty;     // y方向平移
    HKA_F32 rotate; // 旋转（弧度制）
    HKA_F32 aspect; // y方向和x方向比例
    HKA_F32 skew;   // 倾斜量
}MVBI_TRANSFORM_2D_PARAM;

// 缺陷类型
typedef enum _MVBI_EDGE_DEFECT_TYPE
{
    MVBI_EDGE_DEFECT_TYPE_NONE = 0, // 非缺陷
    MVBI_EDGE_DEFECT_TYPE_FLAW = 1, // 缺陷
    MVBI_EDGE_DEFECT_TYPE_GAP  = 2, // 断裂
}MVBI_EDGE_DEFECT_TYPE;

// 边缘缺陷信息
typedef struct _MVBI_EDGE_DEFECT_INFO
{
    MVBI_BOX_F defect_box;    // 缺陷包围框
    HKA_F32    defect_size;   // 缺陷/间隔长度
    HKA_F32    defect_area;   // 缺陷/间隔面积
    HKA_S32    caliper_start; // 缺陷卡尺起始索引
    HKA_S32    caliper_end;   // 缺陷卡尺终止索引
    HKA_S32    defect_type;   // 缺陷类型
}MVBI_EDGE_DEFECT_INFO;

// 调试信息
typedef struct _MVB_DEBUG_INFO
{
    HKA_VOID  *debug_data;    // debug句柄
    HKA_S32    debug_size;    // 信息大小
    HKA_S32    debug_enable;  // debug使能
    HKA_S32    debug_index;   // debug索引号
    HKA_S32    pos_index;     // 位置索引
    HKA_S32    status;        // 状态    
}MVB_DEBUG_INFO;

/***************************************************************************************************
* 图像结构体定义
***************************************************************************************************/
//图像格式（新的类型添加在最后面，保持前向兼容，每种格式按段长度100划分）
typedef enum _MVB_IMAGE_FORMAT
{
	//未知的，未定义数据格式。用户可以根据应用情况另外定义格式变量
	MVB_IMG_UNKNOWN = 0,

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
	MVB_IMG_MONO_08 = 1,    //| 8b   | U08  |        D0           |         S0          |
	//mono12                            //----------------------------------------------------------
	MVB_IMG_MONO_12 = 2,    //| 12b  | U16  |        D0           |         S0          |
	//mono16                            //----------------------------------------------------------
	MVB_IMG_MONO_16 = 3,    //| 16b  | U16  |        D0           |         S0          |
	//mono float 16bit                  //----------------------------------------------------------
	MVB_IMG_MONO_F16 = 4,    //| 16b  | F16  |        D0           |         S0          |
	//mono float 32bit                  //----------------------------------------------------------
	MVB_IMG_MONO_F32 = 5,    //| 32b  | F32  |        D0           |         S0          |
    //mono float 64bit                  //----------------------------------------------------------
    MVB_IMG_MONO_F64 = 6,    //| 64b  | F64  |        D0           |         S0          |
    //mono float 32bit                  //----------------------------------------------------------
    MVB_IMG_MONO_FC32 = 7,    //| 32b  | FC32  |        D0           |         S0          |
    //mono float 64bit                  //----------------------------------------------------------
    MVB_IMG_MONO_FC64 = 8,    //| 64b  | F64  |        D0           |         S0          |
    //mono10                            //----------------------------------------------------------
    MVB_IMG_MONO_10 = 9,      //| 14b  | U16  |        D0           |         S0          |
	//mono14                            //----------------------------------------------------------
	MVB_IMG_MONO_14 = 10,      //| 14b  | U16  |        D0           |         S0          |
    //----------------------------------//----------------------------------------------------------
	//YUV (100~199)                     //| bit  | type |   store position    |        step         |
	//YUV420 Sx(U,V) = 2 Sy(U,V) = 2    //----------------------------------------------------------
	//I420 planar
	MVB_IMG_YUV_I420 = 100,  //| 8b   | U08  |    Y:D0,U:D1,V:D2   |  Y:S0,U:S1,V:S2     |
	//YUV420                            //----------------------------------------------------------
	//YV12 planar
	MVB_IMG_YUV_YV12 = 101,  //| 8b   | U08  |    Y:D0,V:D1,U:D2   |  Y:S0,V:S1,U:S2     |
	//YUV420                            //----------------------------------------------------------
	//NV12 UV packed
	MVB_IMG_YUV_NV12 = 102,  //| 8b   | U08  |    Y:D0,UV:D1       |  Y:S0,UV:S1         |
	//YUV422 Sx(U,V) = 1 Sy(U,V) = 2    //----------------------------------------------------------
	//planar
	MVB_IMG_YUV_422 = 103,  //| 8b   | U08  |    Y:D0,U:D1,V:D2   |  Y:S0,U:S1,V:S2     |
	//YUV422                            //----------------------------------------------------------
	//UYVY packed
	MVB_IMG_YUV_UYVY = 104,  //| 8b   | U08  |    YUV:D0           |  YUV:S0             |
	//YUV444  Sx(U,V) = 1 Sy(U,V) = 1   //----------------------------------------------------------
	//planar
	MVB_IMG_YUV_444 = 105,  //| 8b   | U08  |    Y:D0,U:D1,V:D2   |  Y:S0,U:S1,V:S2     |
	//YUV422                            //----------------------------------------------------------
	//YUYV (YUY2) packed
	MVB_IMG_YUV_YUYV = 106,  //| 8b   | U08  |    YUV:D0           |  YUV:S0             |
	//YUV422                            //----------------------------------------------------------
	//YVYU packed
	MVB_IMG_YUV_YVYU = 107,  //| 8b   | U08  |    YUV:D0           |  YUV:S0             |
	//YUV422                            //----------------------------------------------------------
	//VYUY
	MVB_IMG_YUV_VYUY = 108,  //| 8b   | U08  |    YUV:D0           |  YUV:S0             |
	//YUV420                            //----------------------------------------------------------
	//NV21 VU packed
	MVB_IMG_YUV_NV21 = 109,  //| 8b   | U08  |    Y:D0,VU:D1       |  Y:S0,VU:S1         |
	//YUV411 Sx(U,V) = 4 Sy(U,V) = 1    //----------------------------------------------------------
	//planar
	MVB_IMG_YUV_YUV411 = 130,  //| 8b   | U08  |    Y:D0,U:D1,V:D2   |  Y:S0,U:S1,V:S2     |
	//YUV411                            //----------------------------------------------------------
	//Y411 (Y41P) packed: U0 Y0 V0 Y1 U4 Y2 V4 Y3 Y4 Y5 Y6 Y8 
	MVB_IMG_YUV_Y41P = 131,  //| 8b   | U08  |    YUV:D0           |  YUV:S0             |
	//YVU9 Sx(U,V) = 4 Sy(U,V) = 4      //----------------------------------------------------------
	//planar
	MVB_IMG_YUV_YVU9 = 140,  //| 8b   | U08  |    Y:D0,U:D1,V:D2   |  Y:S0,U:S1,V:S2     |
	//AYUV                              //----------------------------------------------------------
	//planar
	MVB_IMG_YUV_AYUV = 150,  //| 8b   | U08  | A:D0,Y:D1,U:D2,V:D3 | A:S0,Y:S1,U:S2,V:S3 |
	//YUV440  Sx(U,V) = 1 Sy(U,V) = 2   //----------------------------------------------------------
	//planar
	MVB_IMG_YUV_440 = 180,  //| 8b   | U08  |    Y:D0,U:D1,V:D2   |  Y:S0,U:S1,V:S2     |
	//YUV424  Sx(U) = 2 Sy(V) = 2       //----------------------------------------------------------
	//planar
	MVB_IMG_YUV_424 = 181,  //| 8b   | U08  |    Y:D0,U:D1,V:D2   |  Y:S0,U:S1,V:S2     |
	//YUV442  Sy(U) = 2 Sx(V) = 2       //----------------------------------------------------------
	//planar
	MVB_IMG_YUV_442 = 182,  //| 8b   | U08  |    Y:D0,U:D1,V:D2   |  Y:S0,U:S1,V:S2     |
	//----------------------------------//----------------------------------------------------------
	//RGB (200~299)                     //| bit  | type |   store position    |        step         |
	//RBG 3 plane                       //----------------------------------------------------------
	MVB_IMG_RGB_RGB24_P3 = 200,  //| 8b   | U08  |    R:D0,G:D1,B:D2   |  R:S0,G:S1,B:S2     |
	//RGB 3 RGBRGB...                   //----------------------------------------------------------
	MVB_IMG_RGB_RGB24_C3 = 201,  //| 8b   | U08  |    RGB:D0           |  RGB:S0             |
	//RGB 4 plane(alpha)                //----------------------------------------------------------
	MVB_IMG_RGB_RGBA_P4 = 202,  //| 8b   | U08  | R:D0,G:D1,B:D2,A:D3 | R:S0,G:S1,B:S2,A:S3 |
	//RGB 4 RGBARGBA...(alpha)          //----------------------------------------------------------
	MVB_IMG_RGB_RGBA_C4 = 203,  //| 8b   | U08  |    RGBA:D0          |  RGBA:S0            |
	//RGB 4 plane(depth)                //----------------------------------------------------------
	MVB_IMG_RGB_RGBD_P4 = 204,  //| 8b   | U08  | R:D0,G:D1,B:D2,A:D3 | R:S0,G:S1,B:S2,A:S3 |
	//RGB 4 RGBDRGBD...(depth)          //----------------------------------------------------------
	MVB_IMG_RGB_RGBD_C4 = 205,  //| 8b   | U08  |    RGBA:D0          |  RGBA:S0            |
	//RBG 3 plane                       //----------------------------------------------------------
	MVB_IMG_RGB_RGB48_P3 = 206,  //| 16b   | U16  |    R:D0,G:D1,B:D2   |  R:S0,G:S1,B:S2     |
	//RGB 3 RGBRGB...                   //----------------------------------------------------------
	MVB_IMG_RGB_RGB48_C3 = 207,  //| 16b   | U16  |    RGB:D0           |  RGB:S0             |
	//RGB 4 plane(alpha)                //----------------------------------------------------------
	MVB_IMG_RGB_RGBA48_P4 = 208,  //| 16b   | U16  | R:D0,G:D1,B:D2,A:D3 | R:S0,G:S1,B:S2,A:S3 |
	//RGB 4 RGBARGBA...(alpha)          //----------------------------------------------------------
	MVB_IMG_RGB_RGBA48_C4 = 209,  //| 16b   | U16  |    RGBA:D0          |  RGBA:S0            |
	MVB_IMG_RGB_BGR24_P3  = 210,  //| 8b   | U08  |    B:D0,G:D1,R:D2   |  B:S0,G:S1,R:S2     |
	//RGB 3 RGBRGB...                   //----------------------------------------------------------
	MVB_IMG_RGB_BGR24_C3 = 211,  //| 8b   | U08  |    BGR:D0           |  BGR:S0             |
	//RGB 4 plane(alpha)                //----------------------------------------------------------
	MVB_IMG_RGB_BGRA_P4 = 212,  //| 8b   | U08  | B:D0,G:D1,R:D2,A:D3 | B:S0,G:S1,R:S2,A:S3 |
	//RGB 4 RGBARGBA...(alpha)          //----------------------------------------------------------
	MVB_IMG_RGB_BGRA_C4 = 213,  //| 8b   | U08  |    BGRA:D0          |  BGRA:S0            |
	//RGB 4 plane(depth)                //----------------------------------------------------------
	MVB_IMG_RGB_BGRD_P4 = 214,  //| 8b   | U08  | B:D0,G:D1,R:D2,D:D3 | B:S0,G:S1,R:S2,D:S3 |
	//RGB 4 RGBDRGBD...(depth)          //----------------------------------------------------------
	MVB_IMG_RGB_BGRD_C4 = 215,  //| 8b   | U08  |    BGRD:D0          |  BGRD:S0            |
	//RBG 3 plane                       //----------------------------------------------------------
	MVB_IMG_RGB_BGR48_P3 = 216,  //| 16b   | U16  |    B:D0,G:D1,R:D2   |  B:S0,G:S1,R:S2     |
	//RGB 3 RGBRGB...                   //----------------------------------------------------------
	MVB_IMG_RGB_BGR48_C3 = 217,  //| 16b   | U16  |    BGR:D0           |  BGR:S0             |
	//RGB 4 plane(alpha)                //----------------------------------------------------------
	MVB_IMG_RGB_BGRA48_P4 = 218,  //| 16b   | U16  | B:D0,G:D1,R:D2,A:D3 | B:S0,G:S1,R:S2,A:S3 |
	//RGB 4 RGBARGBA...(alpha)          //----------------------------------------------------------
	MVB_IMG_RGB_BGRA48_C4 = 219,  //| 16b   | U16  |    BGRA:D0          |  BGRA:S0            |
	//----------------------------------//----------------------------------------------------------
	//bayer (300~399)                   //| bit  | type |   store position    |        step         |
	//bayer GRGB 10bit                  //----------------------------------------------------------
	MVB_IMG_BAYER_GRBG_10 = 300,  //| 10b  | U16  |    GRBG:D0          |  GRBG:S0            |
	//bayer RGGB 10bit                  //----------------------------------------------------------
	MVB_IMG_BAYER_RGGB_10 = 301,  //| 10b  | U16  |    RGGB:D0          |  RGGB:S0            |
	//bayer RGGB 10bit                  //----------------------------------------------------------
	MVB_IMG_BAYER_BGGR_10 = 302,  //| 10b  | U16  |    BGGR:D0          |  BGGR:S0            |
	//bayer RGGB 10bit                  //----------------------------------------------------------
	MVB_IMG_BAYER_GBRG_10 = 303,  //| 10b  | U16  |    GBRG:D0          |  GBRG:S0            |
	//bayer RGGB 12bit                  //----------------------------------------------------------
	MVB_IMG_BAYER_GRBG_12 = 304,  //| 12b  | U16  |    GRBG:D0          |  GRBG:S0            |
	//bayer RGGB 12bit                  //----------------------------------------------------------
	MVB_IMG_BAYER_RGGB_12 = 305,  //| 12b  | U16  |    RGGB:D0          |  RGGB:S0            |
	//bayer RGGB 12bit                  //----------------------------------------------------------
	MVB_IMG_BAYER_BGGR_12 = 306,  //| 12b  | U16  |    BGGR:D0          |  BGGR:S0            |
	//bayer RGGB 12bit                  //----------------------------------------------------------
	MVB_IMG_BAYER_GBRG_12 = 307,  //| 12b  | U16  |    GBRG:D0          |  GBRG:S0            |
	//bayer RGGB 8bit                  //----------------------------------------------------------
	MVB_IMG_BAYER_GRBG_8  = 308,  //| 8b  | U8  |    GRBG:D0          |  GRBG:S0            |
	//bayer RGGB 8bit                 //----------------------------------------------------------
	MVB_IMG_BAYER_RGGB_8  = 309,  //| 8b  | U8  |    RGGB:D0          |  RGGB:S0            |
	//bayer RGGB 8bit                  //----------------------------------------------------------
	MVB_IMG_BAYER_BGGR_8  = 310,  //| 8b  | U8  |    BGGR:D0          |  BGGR:S0            |
	//bayer RGGB 8bit                  //----------------------------------------------------------
	MVB_IMG_BAYER_GBRG_8  = 311,  //| 8b  | U8  |    GBRG:D0          |  GBRG:S0            |
    //bayer RGGB 16bit                  //----------------------------------------------------------
    MVB_IMG_BAYER_GRBG_16 = 312,  //| 16b  | U16  |    GRBG:D0          |  GRBG:S0            |
    //bayer RGGB 16bit                 //----------------------------------------------------------
    MVB_IMG_BAYER_RGGB_16  = 313,  //| 16b  | U16  |    RGGB:D0          |  RGGB:S0            |
    //bayer RGGB 16bit                  //----------------------------------------------------------
    MVB_IMG_BAYER_BGGR_16  = 314,  //| 16b  | U16  |    BGGR:D0          |  BGGR:S0            |
    //bayer RGGB 16bit                  //----------------------------------------------------------
    MVB_IMG_BAYER_GBRG_16  = 315,  //| 16b  | U16  |    GBRG:D0          |  GBRG:S0            |
    //bayer RGGB 14bit                  //----------------------------------------------------------
    MVB_IMG_BAYER_GRBG_14  = 316,  //| 16b  | U16  |    GRBG:D0          |  GRBG:S0            |
    //bayer RGGB 14bit                 //----------------------------------------------------------
    MVB_IMG_BAYER_RGGB_14  = 317,  //| 16b  | U16  |    RGGB:D0          |  RGGB:S0            |
    //bayer RGGB 14bit                  //----------------------------------------------------------
    MVB_IMG_BAYER_BGGR_14  = 318,  //| 16b  | U16  |    BGGR:D0          |  BGGR:S0            |
    //bayer RGGB 14bit                  //----------------------------------------------------------
    MVB_IMG_BAYER_GBRG_14  = 319,  //| 16b  | U16  |    GBRG:D0          |  GBRG:S0            |
	//----------------------------------//----------------------------------------------------------
	//YCbCr (400~499)                   //| bit  | type |   store position    |        step         |
	//YCCK Sx(U,V) = 1 Sy(U,V) = 1      //----------------------------------------------------------
	//planar                            //----------------------------------------------------------
	MVB_IMG_YCCK_P4 = 400,  //| 8b   | U08  |Y:D0,Cb:D1,Cr:D2,K:D3|Y:S0,Cb:S1,Cr:S2,K:S3|
	//packed  C0 M0 Y0 K0 C1 M1 Y1 K1   //----------------------------------------------------------
	MVB_IMG_YCCK_C4 = 401,  //| 8b   | U08  |    YCCK:D0          |  YCCK:S0            |
	//----------------------------------//----------------------------------------------------------
	//CMYK (500~519)                    //| bit  | type |   store position    |        step         |
	//planar                            //----------------------------------------------------------
	MVB_IMG_CMYK_P4 = 500,  //| 8b   | U08  | C:D0,M:D1,Y:D2,K:D3 | C:S0,M:S1,Y:S2,K:S3 |
	//packed  C0 M0 Y0 K0 C1 M1 Y1 K1   //----------------------------------------------------------
	MVB_IMG_CMYK_C4 = 501   //| 8b   | U08  |    CMYK:D0          |  CMYK:S0            |
	//----------------------------------//----------------------------------------------------------
}MVB_IMAGE_FORMAT;

// 算法库输入图像结构体
typedef struct _MVB_IMAGE
{
	MVB_IMAGE_FORMAT    format;              // 图像格式，按照数据类型HKA_IMAGE_FORMAT赋值
	HKA_S32             width;               // 图像宽度
	HKA_S32             height;              // 图像高度
	HKA_S32             step[4];             // 行间距
	HKA_VOID           *vir_base[4];         // 数据存储虚拟地址
	HKA_VOID           *phy_base[4];         // 数据存储物理地址

} MVB_IMAGE;

//设置配置参数类型（cfg_type），MVBXXX_SetConfig函数使用
typedef enum _MVB_SET_CFG_TYPE
{
    MVB_SET_CFG_SINGLE_PARAM    = 0x0001,    //单个参数
    MVB_SET_CFG_PARAM_LIST      = 0x0002,    //参数列表
    MVB_SET_CFG_DEFAULT_PARAM   = 0x0003,    //默认参数
    MVB_SET_CFG_RESTART_LIB     = 0x0004,    //重启算法库
    MVB_SET_CFG_CALLBACK        = 0x0005,    //回调函数
    MVB_SET_CFG_CHECK_PARAM     = 0x0006,    //单个参数检测
    MVB_SET_CFG_CPU_COREID_MASK = 0x0007,    // 多线程使用核资源的掩膜
    MVB_SET_CFG_MEM_FUNC_PT     = 0x0008,    // 内存申请和释放函数指针
}MVB_SET_CFG_TYPE;

//获取配置参数类型（cfg_type），MVBXXX_GetConfig函数使用
typedef enum _MVB_GET_CFG_TYPE
{
    MVB_GET_CFG_SINGLE_PARAM    = 0x0001,    //单个参数
    MVB_GET_CFG_PARAM_LIST      = 0x0002,    //整个参数表
    MVB_GET_CFG_VERSION         = 0x0003,    //版本信息
    MVB_GET_CFG_ABILITY         = 0x0004,    //算法库能力集
    MVB_GET_CFG_CPU_COREID_MASK = 0x0005,    //多线程使用核资源的掩膜
	MVB_GET_CFG_MEM_FUNC_PT     = 0x0006,    // 内存申请和释放函数指针
}MVB_GET_CFG_TYPE;

// 多线程核信息
typedef struct _MVB_CPU_CORE_INFO
{
	HKA_U64 coreid_mask; // 核id掩膜,bit[0]表示CPU0，bit[1]表示CPU1，以此类推
	HKA_U32 reserved[8]; // reserved
}MVB_CPU_CORE_INFO;

// AES加密相关宏
#define MVB_AES_SOFT_FEATURE_LEN  (16)  // AES软件特征信息长度
#define MVB_AES_HARD_FEATURE_LEN  (16)  // AES硬件特征信息长度
#define MVB_AES_ENC_STR_LEN       (MVB_AES_SOFT_FEATURE_LEN + MVB_AES_HARD_FEATURE_LEN)  // AES信息长度

#if defined(_WIN64) || defined(__x86_64__) || defined(__amd64__) || defined(__aarch64__)
typedef HKA_U64      MVB_SZT;
#else
typedef HKA_U32      MVB_SZT;
#endif

#ifdef __cplusplus        
}
#endif
#endif // MVB_TYPES_H_