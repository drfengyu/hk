/***************************************************************************************************
* File:  MVD_ShapeParamDefine.h
* Note:  Parameter and data struct definition of shape module in namespace VisionDesigner.
*
* Version:  V3.1.0.0
****************************************************************************************************/

#ifndef _MVD_SHAPE_PARAM_DEFINE_H__
#define _MVD_SHAPE_PARAM_DEFINE_H__

namespace VisionDesigner
{
    #define MVD_TEXT_CONTENT_MAX_LEN 4096 //文本图形类内容最大长度
    #define MVD_TEXT_FONT_FACE_SIZE 32   //文本图形类字体类型字符串最大长度

    /** @struct MVD_SHAPE_TYPE
     *  @brief  Shape type designed in this module.
     */
    typedef enum _MVD_SHAPE_TYPE_
    {
        MvdShapeUndefined      = 0,
        MvdShapeStraightLine,
        MvdShapeLineSegment,
        MvdShapeRadialLine,
        MvdShapeTriangle,
        MvdShapeRectangle,
        MvdShapeCircle,
        MvdShapeEllipse,
        MvdShapePointSet,
        MvdShapeText,
        MvdShapeAnnularSector,
        MvdShapePolygon,
        MvdShapeParallelogram,
        MvdShapePolylineSegment,
    }MVD_SHAPE_TYPE;

    /** @struct MVD_DASH_STYLE
     *  @brief  Specifies the style of dashed lines drawn with a System.Drawing.Pen object.
     */
    // Summary:
    typedef enum _MVD_DASH_STYLE_
    {
        MvdDashSolid = 0,         //     Specifies a solid line.
        MvdDashDash = 1,          //     Specifies a line consisting of dashes.
        MvdDashDot = 2,           //     Specifies a line consisting of dots.
        MvdDashDashDot = 3,       //     Specifies a line consisting of a repeating pattern of dash-dot.
        MvdDashDashDotDot = 4,    //     Specifies a line consisting of a repeating pattern of dash-dot-dot.
    }MVD_DASH_STYLE;

    /** @struct MVD_COLOR
     *  @brief  color
     */
    typedef struct _MVD_COLOR_
    {
        unsigned char       nR;
        unsigned char       nG;
        unsigned char       nB;
        unsigned char       nAlpha;
    }MVD_COLOR;

    /** @struct MVD_POINT_S
     *  @brief  a point - signed short type
     */
    typedef struct _MVD_POINT_S
    {
        signed short    sX;
        signed short    sY;
    }MVD_POINT_S;

    /** @struct MVD_POINT_I
     *  @brief  a point - signed int type
     */
    typedef struct MVD_POINT_I__
    {
        signed int    nX;
        signed int    nY;
    } MVD_POINT_I;

    /** @struct MVD_POINT_F
     *  @brief  a point - float type
     */
    typedef struct MVD_POINT_F__
    {
        float    fX;
        float    fY;
    } MVD_POINT_F;

    /** @struct MVD_POINT_DF
     *  @brief  a point - double type
     */
    typedef struct MVD_POINT_DF__
    {
        double    dfX;
        double    dfY;
    } MVD_POINT_DF;

    /** @struct MVD_SIZE_I
     *  @brief  size description - signed int type
     */
    typedef struct MVD_SIZE_I__
    {
        signed int nWidth;
        signed int nHeight;
    } MVD_SIZE_I;

    /** @struct MVD_SIZE_F
     *  @brief  size description - float type
     */
    typedef struct MVD_SIZE_F__
    {
        float fWidth;
        float fHeight;
    }MVD_SIZE_F;
    /** @struct MVD_RECT_I
    *  @brief  rectangle description - signed int type
    */
    typedef struct _MVD_RECT_I_
    {
        int nX;         //the left top x of the rectangle
        int nY;         //the left top y of the rectangle
        int nWidth;     //the width of the rectangle
        int nHeight;    //the height of the rectangle
    }MVD_RECT_I;
    /** @struct MVD_RECT_F
    *  @brief  rectangle description - float type
    */
    typedef struct _MVD_RECT_F_
    {
        float fX;       //the left top x of the rectangle
        float fY;       //the left top y of the rectangle
        float fWidth;   //the width of the rectangle
        float fHeight;  //the height of the rectangle
    }MVD_RECT_F;

    /*
    *  @struct   MVD_TEXT_POSITION_TYPE
    *  @brief    文本图形位置类型
    */
    typedef enum _MVD_TEXT_POSITION_TYPE_
    {
        MVD_TP_UNDEFINED=0,        ///< 未定义文本图形位置类型
        MVD_TP_TOPLEFT=1,          ///< 左上角
        MVD_TP_TOPMIDDLE=2,        ///< 中上
        MVD_TP_TOPRIGHT=3,         ///< 右上角
        MVD_TP_MIDDLELEFT=4,       ///< 左中
        MVD_TP_CENTER=5,           ///< 中心
        MVD_TP_MIDDLERIGHT=6,      ///< 右中
        MVD_TP_BOTTOMLEFT=7,       ///< 左下角
        MVD_TP_BOTTOMMIDDLE=8,     ///< 中下
        MVD_TP_BOTTOMRIGHT=9,      ///< 右下角
    }MVD_TEXT_POSITION_TYPE;


    /*
    *  @struct   MVD_TEXT_POSITION
    *  @brief    文本图形位置，示例：fX=100,fY=100,enType=MVD_TP_TOPRIGHT,表明文本左上角的坐标为(100,100)
    */
    typedef struct _MVD_TEXT_POSITION_
    {
        float fX;                           ///< 坐标X
        float fY;                           ///< 坐标Y
        MVD_TEXT_POSITION_TYPE enType;      ///< 文本图形位置类型
    }MVD_TEXT_POSITION;

}

#endif // _MVD_SHAPE_PARAM_DEFINE_H__
