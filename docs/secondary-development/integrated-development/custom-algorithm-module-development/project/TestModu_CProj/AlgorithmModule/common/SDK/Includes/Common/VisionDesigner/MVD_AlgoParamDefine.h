/***************************************************************************************************
* File:  MVD_AlgoParamDefine.h
* Note:  Algorithm-dependent common data struct definition in namespace VisionDesigner.
*
* Version:  V3.2.0.3
****************************************************************************************************/

#ifndef _MVD_ALGO_PARAM_DEFINE_H__
#define _MVD_ALGO_PARAM_DEFINE_H__

#include "MVD_ShapeParamDefine.h"

namespace VisionDesigner
{
    /************************************************************************/
    /*                               标定类                                */
    /************************************************************************/
    /** @struct _MVD_CALIBBOARD_TYPE__
     *  @brief  Calibboard type - enum type
     */
    enum _MVD_CALIBBOARD_TYPE__
    {
        MVD_CALIBBOARD_CHECKER = 1, // Checker Board
        MVD_CALIBBOARD_CIRCLE = 2, // Circle Board
        MVD_CALIBBOARD_HKA_SPARSE_I = 7,   // 海康I型标定板
        MVD_CALIBBOARD_HKA_DENSE_II = 6,   // 海康II型标定板
        MVD_CALIBBOARD_RSCODE_SIGN_FOUR = 3, // 海康I型标定板(V3.3后定义更新为MVD_CALIBBOARD_TYPE_HKA_SPARSE_I)
        MVD_CALIBBOARD_RSCODE_SIGN = 4 // 海康II型标定板(V3.3后定义更新为MVD_CALIBBOARD_TYPE_HKA_DENSE_II)
    };

    /** @struct _MVD_CALIBBOARD_IMAGE_TYPE__
     *  @brief  Calibboard image type - enum type
     */
    enum _MVD_CALIBBOARD_IMAGE_TYPE__
    {
        MVD_CALIBBOARD_OFFSET_IMAGE = 1, // 平移图像
        MVD_CALIBBOARD_ROTATE_IMAGE = 2 // 旋转图像
    };

    /** @struct _MVD_CALIBBOARD_COORDINATE_MODE__
     *  @brief  Calibboard coordinate mode - enum type
     */
    enum _MVD_CALIBBOARD_COORDINATE_MODE__
    {
        MVD_COORD_MODE_LEFT_HANDED = 1, // Left-handed coordinate system
        MVD_COORD_MODE_RIGHT_HANDED = 2 // Right-handed coordinate system
    };

    /** @enum _MVD_CAMERA_MODE__
     *  @brief  camera mode - enum type
     */
    enum _MVD_CAMERA_MODE__
    {
        MVD_CAMERA_MODE_STATIC_UP = 1,
        MVD_CAMERA_MODE_STATIC_DOWN = 2,
        MVD_CAMERA_MODE_MOVE = 3
    };

    /** @enum _MVD_MAP_CALIB_MODE__
    *  @brief  map calib mode - enum type
    */
    enum _MVD_MAP_CALIB_MODE__
    {
        MVD_MAP_CALIB_MODE_TWO_IMAGE = 1,
        MVD_MAP_CALIB_MODE_TWO_FILE = 2,
    };
    /** @enum _MVD_CALIB_MOVE_TYPE__
    *  @brief  map calib mode - enum type
    */
    enum _MVD_CALIB_MOVE_TYPE__
    {
        MVD_MAP_CALIB_MOVE_TYPE_OFFSET = 1,
        MVD_MAP_CALIB_MOVE_TYPE_ROTATE = 2,
    };
    /************************************************************************/
    /*                               拼接类                                */
    /************************************************************************/
    /** @struct _MVD_STITCH_CHECKERBOARD_SUBPIXEL_WIN_AUTO_TYPE_
    *  @brief  subpixel window auto type - enum type
    */
    enum _MVD_STITCH_CHECKERBOARD_SUBPIXEL_WIN_AUTO_TYPE__
    {
        MVD_STITCH_CHECKERBOARD_SUBP_WIN_AUTO = 1, // 自适应
        MVD_STITCH_CHECKERBOARD_SUBP_WIN_MANUAL = 2 // 设置值
    };

    /** @struct _MVD_STITCH_PATTERN_CREATE_PARAM__
    *  @brief  Pattern create param - struct type
    */
    struct _MVD_STITCH_PATTERN_CREATE_PARAM__
    {
        bool bFilterFlag; // 中值滤波标记，默认值true
        _MVD_STITCH_CHECKERBOARD_SUBPIXEL_WIN_AUTO_TYPE__ enSubPixelWinMode; // 亚像素窗口模式,默认值1
        int nSubPixelWinSize; // 亚像素窗口大小[3,100], 默认值7
        int nGrayContrast; // 灰度对比度[1,255], 默认值15
        int nReserved[8]; // 保留字节
    };

    /************************************************************************/
    /*                               定位类                                */
    /************************************************************************/
    /** @enum  _MVD_EDGEPOINT_STATUS__
     *  @brief Find status of the edge point
     */
    enum _MVD_EDGEPOINT_STATUS__
    {
        MVD_EDGEPOINT_STATUS_USED = 0x0001,    // Successfully found and used, default value
        MVD_EDGEPOINT_STATUS_NO_USED = 0x0002,    // Successfully found but not used
        MVD_EDGEPOINT_STATUS_NO_FIND = 0x0003     // Fail to find
    };

    /** @enum  _MVD_EDGE_POLARITY__
     *  @brief Type of the polarity of the edge point
     */
    enum _MVD_EDGE_POLARITY__
    {
        MVD_EDGE_POLARITY_DARK_TO_BRIGHT = 0x0001,    // From black to white, default value
        MVD_EDGE_POLARITY_BRIGHT_TO_DARK = 0x0002,    // From white to black
        MVD_EDGE_POLARITY_BOTH = 0x0003     // both
    };

    /** @enum  _MVD_EDGE_POLARITY_EX__
    *  @brief Type of the polarity of the edge point
    */
    enum _MVD_EDGE_POLARITY_EX__
    {
        MVD_EDGE_POLARITY_DARK_TO_BRIGHT_EX = 0x0001,    // 由黑到白
        MVD_EDGE_POLARITY_BRIGHT_TO_DARK_EX = 0x0002,    // 由白到黑
        MVD_EDGE_POLARITY_MIXED_EX = 0x0003,     // 由黑到白 & 由白到黑(同一条线段中点集有两种极性点)
        MVD_EDGE_POLARITY_EITHER_EX = 0x0004     // 由黑到白 | 由白到黑(同一条线段中点集有一种极性点)
    };

    /** @enum  _MVD_POSITION__
     *  @brief 方位
     */
    enum _MVD_POSITION__
    {
        MVD_POSITION_TOP = 0x0001,    // Top
        MVD_POSITION_RIGHT = 0x0002,    // Right
        MVD_POSITION_BOTTOM = 0x0003,    // Bottom
        MVD_POSITION_LEFT = 0x0004,    // Left
    };

    /** @enum  MVD_CALIPERTOOL_EDGEMODE
     *  @brief Type of the edge mode for the caliper
     */
    typedef enum _MVD_CALIPERTOOL_EDGEMODE__
    {
        MVD_CALIPERTOOL_EDGEMODE_SINGLE_EDGE = 0x0001,    // Caliper Tool Work mode : SingleEdge, default value
        MVD_CALIPERTOOL_EDGEMODE_EDGE_PAIR = 0x0002,    // Caliper Tool Work mode : EdgePair
    };

    /** @struct _MVD_FIDUCIAL_POINT_F__
    *  @brief  fiducial pose point Info - float type
    */
    struct _MVD_FIDUCIAL_POINT_F__
    {
        MVD_POINT_F stPosition;
        float fAngle;
        float fScaleX;
        float fScaleY;

        int nReserved[6];
    };

    /** @struct _MVD_POSFIX_MODE__
     *  @brief  Position Fix Mode - enum type
     */
    enum _MVD_POSFIX_MODE__
    {
        MVD_POSFIX_MODE_NONE = 0x0001,  // Do not make position fixture
        MVD_POSFIX_MODE_HORI = 0x0002,  // Position fixture horizontally
        MVD_POSFIX_MODE_VERT = 0x0003,  // Position fixture vertically
        MVD_POSFIX_MODE_HV = 0x0004,  // Position fixture both horizontally and vertically
        MVD_POSFIX_MODE_HVA = 0x0005,  // Angle fixture both horizontally and vertically
        MVD_POSFIX_MODE_HVAS = 0x0006,  // Angle fixture both horizontally and vertically, support scale
    };


    /************************************************************************/
    /*                               测量类                                */
    /************************************************************************/
    /** @enum  _MVD_MEASURE_C2C_TYPES__
     *  @brief Positional relationship between circle and circle
     */
    enum _MVD_MEASURE_C2C_TYPES__
    {
        MVD_MEASURE_C2C_UNDEFINED = 0x00000000,     // Undefined
        MVD_MEASURE_C2C_CONTAIN = 0x00000001,     // Contain
        MVD_MEASURE_C2C_INSCRIBE = 0x00000002,     // Inscribe
        MVD_MEASURE_C2C_INTERSECT = 0x00000003,     // Intersect
        MVD_MEASURE_C2C_EXCIRCLE = 0x00000004,     // External cutting
        MVD_MEASURE_C2C_DEVIATION = 0x00000005,     // Deviation
    };


    /************************************************************************/
    /*                             预处理类                             */
    /************************************************************************/
    /** @enum _MVD_IMGFIX_MODE__
     *  @brief  Image Fix Mode
     */
    enum _MVD_IMGFIX_MODE__
    {
        MVD_IMGFIX_MODE_NONE = 0x0001,  // Do not make fixture
        MVD_IMGFIX_MODE_HORI = 0x0002,  // Fixture horizontally
        MVD_IMGFIX_MODE_VERT = 0x0003,  // Fixture vertically
        MVD_IMGFIX_MODE_HV = 0x0004,  // Fixture both horizontally and vertically
        MVD_IMGFIX_MODE_HVA = 0x0005,  // Angle fixture both horizontally and vertically
        MVD_IMGFIX_MODE_HVAS = 0x0006,  // Angle fixture both horizontally and vertically, support scale
    };

    /** @struct _MVD_PREPRO_FIDUCIAL_POINT_F__
     *  @brief  fiducial pose point Info - float type
     */
    struct _MVD_PREPRO_FIDUCIAL_POINT_F__
    {
        MVD_POINT_F stBasisPoint;
        float fBasisAngle;
        float fScaleX;
        float fScaleY;

        int nReserved[6];
    };

    /************************************************************************/
    /*                              识别类                             */
    /************************************************************************/
    /** @enum _MVD_1DCODE_TYPE__
     *  @brief  1D Code Type - enum type
     */
    enum _MVD_1DCODE_TYPE__
    {
        MVD_1DCODE_NONE = 0, // unsupport
        MVD_1DCODE_EAN8 = 1, // EAN8 Code
        MVD_1DCODE_UPCE = 2, // UPCE Code
        MVD_1DCODE_UPCA = 3, // UPCA Code
        MVD_1DCODE_EAN13 = 4, // EAN13 Code
        MVD_1DCODE_ISBN13 = 5, // ISBN13 Code
        MVD_1DCODE_CODABAR = 6, // codabar Code
        MVD_1DCODE_ITF25 = 7, // itf 25 Code
        MVD_1DCODE_39 = 8, // Code 39
        MVD_1DCODE_93 = 9, // Code 93
        MVD_1DCODE_128 = 10, // Code 128
    };

    /** @enum _MVD_TDCODE_TYPE__
     *  @brief  2DCode Type - enum type
     */
    enum _MVD_TDCODE_TYPE__
    {
        MVD_2DCODE_NONE = 0, // 无可识别条码
        MVD_2DCODE_DM = 1, // DM码
        MVD_2DCODE_QR = 2, // QR码
    };

    /** @enum _MVD_SYMBOL_VERIFY_STANDARD__
    *  @brief  Grade Standard
    */
    enum _MVD_SYMBOL_VERIFY_STANDARD__
    {
        MVD_SYMBOL_VERIFY_ISO_STANDARD_15415 = 1,         // iso 15415标准
        MVD_SYMBOL_VERIFY_ISO_STANDARD_29158 = 2,          // iso 29158标准
        MVD_SYMBOL_VERIFY_ISO_STANDARD_15416 = 3,         // iso 15416标准
    };

    /** @enum _MVD_SYMBOL_VERIFY_LABEL__
    *  @brief  Verify label
    */
    enum _MVD_SYMBOL_VERIFY_LABEL__
    {
        MVD_SYMBOL_VERIFY_LABEL_STANDARD = 1,         // 码评级完全按照iso标准
        MVD_SYMBOL_VERIFY_LABEL_CUSTOM = 2,         // 部分指标采用定制
    };

    enum _MVD_SYMBOL_VERIFY_PROCESS_TYPE__
    {
        MVD_SYMBOL_VERIFY_PROCESS_TYPE_I = 1,   // 只支持DM码,效果较优
        MVD_SYMBOL_VERIFY_PROCESS_TYPE_II = 2,   // 支持DM码和QR码
    };

    /** @enum  _MVDOCR_FILTER_TYPE__
     *  @brief 字符过滤类型
     */
    typedef enum _MVDOCR_FILTER_TYPE__
    {
        MVDOCR_FILTER_NO = 0,    // 不过滤
        MVDOCR_FILTER_NUMBERONLY = 1,    // 只允许数字
        MVDOCR_FILTER_UPPERLOWERCASEBOTH = 2,    // 只允许字母
        MVDOCR_FILTER_UPPERCASEONLY = 3,    // 只允许大写字母
        MVDOCR_FILTER_LOWERCASEONLY = 4,    // 只允许小写字母
        MVDOCR_FILTER_SPECIALONLY = 5,    // 只允许特殊字符
        MVDOCR_FILTER_SPACE = 6,    // 只允许空格,CNNOCR只要过滤类型设为空格，识别结果强制转为空格，传统OCR如果识别结果不为空格，则返回问号
        MVDOCR_FILTER_CUSTOM = 7     // 自定义过滤字符
    };

    /** @enum  _MVDOCR_FILTER__
     *  @brief 字符过滤器
     */
    typedef struct _MVDOCR_FILTER__
    {
        _MVDOCR_FILTER_TYPE__ enFilterType;                // 字符过滤类型
        char               pFilterValue[128];           // 与过滤类型有关，默认为空；e.g.自定义模式下需指定过滤字符串
        int                nReserved[7];                // 保留字节
    };

    /** @enum  _MVDGEOFIND_CALIPER_ROI_MODE__
    *  @brief 圆查找/直线查找输入中的卡尺区域输入模式
    */
    typedef enum _MVDGEOFIND_RUNNING_MODE__
    {
        MVDGEOFIND_RUNNING_MODE_CALCULATE_AND_FIND = 0x0000, //计算ROI相关并执行查找 0
        MVDGEOFIND_RUNNING_MODE_ONLY_CALCULATE     = 0x0001, //仅计算ROI相关输出 1
        MVDGEOFIND_RUNNING_MODE_ONLY_FIND          = 0x0002  //仅执行查找(输出中ROI相关已知)2

    };

    /************************************************************************/
    /*                            缺陷检测类                            */
    /************************************************************************/
    /** @enum  _MVD_EDGEINSP_EDGE_FLAW_TYPE__
     *  @brief Type of the flaw of the edge inspection
     */
    enum _MVD_EDGEINSP_SINGLE_EDGE_FLAW_TYPE__
    {
        MVD_EDGEINSP_SINGLE_FLAW_TYPE_EDGE_OFFSET = 0x0006, // 边缘位置偏移
        MVD_EDGEINSP_SINGLE_FLAW_TYPE_EDGE_ROUGH = 0x0007, // 边缘凸起或凹坑缺陷
        MVD_EDGEINSP_SINGLE_FLAW_TYPE_EDGE_CRACK = 0x0008, // 边缘断裂缺陷
        MVD_EDGEINSP_SINGLE_FLAW_TYPE_EDGE_GRAD = 0x0009, // 边缘阶梯差缺陷
    };

    /** @enum  _MVD_EDGEINSP_EDGE_FLAW_TYPE__
     *  @brief Type of the flaw of the edge inspection
     */
    enum _MVD_EDGEINSP_EDGE_PAIR_FLAW_TYPE__
    {
        MVD_EDGEINSP_FLAW_TYPE_EDGE_WIDTH = 0x0001, // 边缘对宽度缺陷
        MVD_EDGEINSP_FLAW_TYPE_EDGE_OFFSET = 0x0002, // 边缘对位置偏移
        MVD_EDGEINSP_FLAW_TYPE_EDGE_ROUGH = 0x0003, // 边缘对阶梯缺陷
        MVD_EDGEINSP_FLAW_TYPE_EDGE_CRACK = 0x0004, // 边缘对断裂缺陷
        MVD_EDGEINSP_FLAW_TYPE_EDGE_BUBBLE = 0x000A, // 边缘对气泡缺陷
    };

     /** @enum  _MVD_EDGEINSP_FLAW_DEFECT_TYPE__
     *  @brief Type of the flaw
     */
    enum _MVD_EDGEINSP_FLAW_DEFECT_TYPE__
    {
        MVD_EDGEINSP_FLAW_DEFECT_TYPE_NONE = 0, // 非缺陷
        MVD_EDGEINSP_FLAW_DEFECT_TYPE_FLAW = 1, // 缺陷
        MVD_EDGEINSP_FLAW_DEFECT_TYPE_GAP  = 2, // 断裂
    };

    /** @enum  _MVD_MKINSP_METHOD_TYPE__
     *  @brief Character inspection method
     */
    enum _MVD_MKINSP_METHOD_TYPE__
    {
        MVD_MKINSP_COAR_CORRE = 1, // 相关法
        MVD_MKINSP_FINE_MEAN_STD = 2, // 均值标准差
    };

    /** @enum  _MVD_BEAD_GUIDE_RUNNING_MODE__
     *  @brief bead guide running mode
     */
    enum _MVD_BEAD_GUIDE_RUNNING_MODE__
    {
        MVD_BEAD_GUIDE_FIX_POINT = 0, // 按胶路固定点
        MVD_BEAD_GUIDE_FIND_EDGE = 1, // 固定胶路查找边缘
    };

    /************************************************************************/
    /*                            颜色处理类                            */
    /************************************************************************/
    /** @enum  _MVD_COLOR_SPACE_TYPE__
    *  @brief Color space type
    */
    enum _MVD_COLOR_SPACE_TYPE__
    {
        MVD_COLOR_SPACE_RGB = 1,   // RGB颜色空间
        MVD_COLOR_SPACE_HSV = 2,   // HSV颜色空间
        MVD_COLOR_SPACE_HSI = 3,   // HSI颜色空间
        MVD_COLOR_SPACE_YUV = 4    // YUV颜色空间(颜色抽取不支持)
    };

    /** @enum  _MVD_COLOR_EXTRACT_SINGLE_RANGE__
    *  @brief Color extract range param
    */
    struct _MVD_COLOR_EXTRACT_SINGLE_RANGE__
    {
        int nC1LowTolerance;        // 第一通道(R or H)的低容忍值
        int nC1HighTolerance;       // 第一通道(R or H)的高容忍值
        int nC2LowTolerance;        // 第二通道(G or S)的低容忍值
        int nC2HighTolerance;       // 第二通道(G or S)的高容忍值
        int nC3LowTolerance;        // 第三通道(B or V)的低容忍值
        int nC3HighTolerance;       // 第三通道(B or V)的高容忍值
        bool bReverseEnable;        // 反转使能   true表示反转，false表示不反转
        _MVD_COLOR_SPACE_TYPE__ enColorSpace;            // 颜色空间  //每个范围均可单独设置颜色空间
        int nReserved[8]; // 保留字节
    };

}

#endif // _MVD_ALGO_PARAM_DEFINE_H__
