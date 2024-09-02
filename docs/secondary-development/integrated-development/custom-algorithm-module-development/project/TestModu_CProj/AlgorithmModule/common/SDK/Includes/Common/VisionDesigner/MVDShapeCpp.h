/***************************************************************************************************
* File:  MVDShapeCpp.h
* Note:  Interface definition of shape module.
*
* Version：3.4.0.3
* Date:  2021-01
****************************************************************************************************/

#ifndef _MVD_SHAPE_CPP_H_
#define _MVD_SHAPE_CPP_H_

#include "MVD_Export.h"
#include "MVD_ShapeParamDefine.h"
#include "MVD_ErrorDefine.h"


namespace VisionDesigner
{
    /* 图形基类，接口作用;e.g.各Tool支持不定的ROI类型 */
    class IMvdShape
    {
    //Constructor and Destructor
    protected:
        /*  note: Constructs a new instance of this class.  */
        explicit IMvdShape() {}
        /*  note: Constructs a new instance of this class as a deep copy of the given instance.  */
        virtual ~IMvdShape() {}
        
    public:
        virtual IMvdShape& operator=(const IMvdShape& refShape) { return *this;}
        virtual bool operator==(IMvdShape const& refShape) { return false; }

        //properties
    public:
        /**
         * @par 说明
         * 图形的类型
         * @par 权限
         * 只读
         */
        /* Get current shape type. */
        virtual MVD_SHAPE_TYPE GetShapeType() const =0;
        /**
         * @par 说明
         * 图形的名字，若未命名形状，则返回UntitledName。
         * @par 权限
         * 读写
         */
        /* note: Get name of this shape. Return "UntitledName" if you have not specified the name. */
        virtual const char* GetShapeName() const = 0;
        /**
         * @par 说明
         * 图形的名字，若未命名形状，则返回UntitledName。
         * @par 权限
         * 读写
         */
        /* note: Set name of this shape. */
        virtual void SetShapeName(const char pcName[64]) = 0;
        /**
         * @par 说明
         * 图形边框宽度
         * @par 权限
         * 读写
         */
        /* note: Get border width of this shape. */
        virtual unsigned int GetBorderWidth() const = 0;
        /**
         * @par 说明
         * 图形边框宽度
         * @par 权限
         * 读写
         */
        /* note: Set border width of this shape. */
        virtual void SetBorderWidth(unsigned int nBorderWdith) = 0;
        /**
         * @par 说明
         * 图形边框类型
         * @par 权限
         * 读写
         */
        /* note: Get border style of this shape. */
        virtual MVD_DASH_STYLE GetBorderStyle() const = 0;
        /**
         * @par 说明
         * 图形边框类型
         * @par 权限
         * 读写
         */
        /* note: Set border style of this shape. */
        virtual void SetBorderStyle(MVD_DASH_STYLE enBorderStyle) = 0;
        /**
         * @par 说明
         * 图形边框颜色
         * @par 权限
         * 读写
         */
        /* note: Get border color of this shape. */
        virtual MVD_COLOR GetBorderColor() const = 0;
        /**
         * @par 说明
         * 图形边框颜色
         * @par 权限
         * 读写
         */
        /* note: Set border color of this shape. */
        virtual void SetBorderColor(MVD_COLOR enColor) = 0;
        /**
         * @par 说明
         * 图形填充色
         * @par 权限
         * 读写
         */
        /* note: Get the fill color of this shape. Whether to implement depends on the specific shape type. Not supported for non-closed shapes. */
        virtual MVD_COLOR GetFillColor() const;
        /**
         * @par 说明
         * 图形填充色
         * @par 权限
         * 读写
         */
        /* note: Set the fill color of this shape. Whether to implement depends on the specific shape type. Not supported for non-closed shapes. */
        virtual void SetFillColor(MVD_COLOR enFillColor);

    };
    /* 图形基类扩展接口，接口作用;e.g.各Tool支持不定的ROI类型 */
    class IMvdShapeEx
    {
        //Constructor and Destructor
    protected:
        /*  note: Constructs a new instance of this class.  */
        explicit IMvdShapeEx() {}
        /*  note: Constructs a new instance of this class as a deep copy of the given instance.  */
        virtual ~IMvdShapeEx() {}

    public:
        virtual IMvdShapeEx& operator=(const IMvdShapeEx& refShape) { return *this;}
        virtual bool operator==(IMvdShapeEx const& refShape) { return false; }

        //properties
    public:
        /**
        * @par 说明
        * 获取点到图形之间的距离，目前仅支持线段和圆形
        * @par 权限
        * 读写
        */
        /* note: Get the distance from the given point to this shape,only support line segment and circle. */
        virtual float Measure(MVD_POINT_F stPoint);
        /**
        * @par 说明
        * 获取图形之间的距离，目前仅支持线段和圆形
        * @par 权限
        * 读写
        */
        /* note: Get the distance from the given shape to this shape,only support line segment and circle. */
        virtual float Measure(IMvdShape* pstShape);
        /**
        * @par 说明
        * 获取图形的外接矩形，不支持文本图形
        * @par 权限
        * 读写
        */
        /* note: Get the bounding rectangle of the given shape,text is not supported. */
        virtual MVD_RECT_F GetBoundingRect()const;

    };
    /* Class that represents a line segment. */
    class IMvdLineSegmentF : public IMvdShape,public IMvdShapeEx
    {
    //Constructor and Destructor
    protected:
        explicit IMvdLineSegmentF() {}
        explicit IMvdLineSegmentF(MVD_POINT_F stStartPoint, MVD_POINT_F stEndPoint) {}
        virtual ~IMvdLineSegmentF() {}

    public:
        virtual IMvdLineSegmentF& operator=(const IMvdShape& refShape) { return *this; }
        virtual IMvdLineSegmentF& operator=(const IMvdLineSegmentF& refLine) { return *this; }
        virtual bool operator==(IMvdShape const& refShape) { return false; }
        virtual bool operator==(IMvdLineSegmentF const& refLine) { return false; }

    // Clone methods
    public:
        /**
         * @brief 克隆线段描述类对象
         * @param 无
         * @return 成功，返回线段描述类对象;失败，抛出异常。
         * @par 注解
         * 
         */
        /* Returns a deep copy of this class instance. Derived classes that implement 
           Clone should override this method. Other clients who wish to clone this instance 
            should call IMvdLineSegmentF.Clone.*/
        virtual IMvdLineSegmentF* Clone() = 0;

    //properties
    public:
        MVD_SHAPE_TYPE GetShapeType() const { return MvdShapeLineSegment; }
        /**
         * @par 说明
         * 线段起点
         * @par 权限
         * 读写
         */
        /* note: Start point of this line. */
        virtual MVD_POINT_F GetStartPoint() const = 0;
        /**
         * @par 说明
         * 线段起点
         * @par 权限
         * 读写
         */
        virtual void SetStartPoint(MVD_POINT_F stStartPoint) = 0;
        /**
         * @par 说明
         * 线段终点
         * @par 权限
         * 读写
         */
        /* note: End point of this line. */
        virtual MVD_POINT_F GetEndPoint() const = 0;
        /**
         * @par 说明
         * 线段终点
         * @par 权限
         * 读写
         */
        virtual void SetEndPoint(MVD_POINT_F stEndPoint) = 0;
        /**
         * @par 说明
         * 线段倾斜角度
         * @par 权限
         * 只读
         */
        /* note: Angle of this line((-180,180]). The Angle between the vector from the starting point to the end point and the positive X-axis. */
        virtual float GetAngle() = 0;
        /**
         * @par 说明
         * 图形是否允许交互
         * @par 权限
         * 只读
         */
        virtual bool GetInteraction() = 0;
        /**
         * @par 说明
         * 图形是否允许交互
         * @par 权限
         * 只读
         */
        virtual void SetInteraction(bool bInteraction) = 0;
    };

    /* Class that represents a text. */
    class IMvdTextF : public IMvdShape,public IMvdShapeEx
    {
        //Constructor and Destructor
    protected:
        explicit IMvdTextF() {}
        explicit IMvdTextF(float fCenterX, float fCenterY,const char pcContent[MVD_TEXT_CONTENT_MAX_LEN]) {}
        virtual ~IMvdTextF() {}

    public:
        virtual IMvdTextF& operator=(const IMvdShape& refShape) { return *this; }
        virtual IMvdTextF& operator=(const IMvdTextF& refRect) { return *this; }
        virtual bool operator==(IMvdShape const& refShape) { return false; }
        virtual bool operator==(IMvdTextF const& refRect) { return false; }

        // Clone methods
    public:
        /**
        * @brief 克隆文本描述类对象
        * @param 无
        * @return 成功，返回文本描述类对象;失败，抛出异常。
        * @par 注解
        * 
        */
        /* Returns a deep copy of this class instance. Derived classes that implement 
        Clone should override this method. Other clients who wish to clone this instance 
        should call IMvdTextF.Clone.*/
        virtual IMvdTextF* Clone() = 0;

        //properties
    public:
        MVD_SHAPE_TYPE GetShapeType() const {return MvdShapeText;}
        /**
        * @par 说明
        * 文本中心X坐标
        * @par 权限
        * 读写
        */
        /* note: Center X coordinate of this text. */
        virtual float GetCenterX() const = 0;
        /**
        * @par 说明
        * 文本中心X坐标
        * @par 权限
        * 读写
        */
        virtual void SetCenterX(float fCenterX) = 0;
        /**
        * @par 说明
        * 文本中心Y坐标
        * @par 权限
        * 读写
        */
        /* note: Center Y coordinate of this text. */
        virtual float GetCenterY() const = 0;
        /**
        * @par 说明
        * 文本中心Y坐标
        * @par 权限
        * 读写
        */
        virtual void SetCenterY(float fCenterY) = 0;
        /**
        * @par 说明
        * 字体宽度
        * @par 权限
        * 读写
        */
        /* note: Width of this text. */
        virtual unsigned int GetFontWidth() const = 0;
        /**
        * @par 说明
        * 字体宽度
        * @par 权限
        * 读写
        */
        virtual void SetFontWidth(unsigned int nWidth) = 0;
        /**
        * @par 说明
        * 字体类型
        * @par 权限
        * 读写
        * @par 注解
        * 获取文本字体类型，如“Arial”,“宋体”。。。
        */
        /* note: Face name of this text. */
        virtual void GetFontFaceName(char pcFaceName[MVD_TEXT_FONT_FACE_SIZE]) const = 0;
        /**
        * @par 说明
        * 字体类型
        * @par 权限
        * 读写
        * @par 注解
        * 设置文本字体类型，如“Arial”,“宋体”。。。
        */
        /* note: Face name of this text. */
        virtual void SetFontFaceName(const char pcFaceName[MVD_TEXT_FONT_FACE_SIZE]) = 0;
        /**
        * @par 说明
        * 文本内容
        * @par 权限
        * 读写
        */
        virtual void GetContent(char pcContent[MVD_TEXT_CONTENT_MAX_LEN]) const = 0;
        /**
        * @par 说明
        * 文本内容
        * @par 权限
        * 读写
        */
        virtual void SetContent(const char pcContent[MVD_TEXT_CONTENT_MAX_LEN]) = 0;
        /**
        * @par 说明
        * 文本角度，范围(-180,180]
        * @par 权限
        * 读写
        * @par 注解
        * 角度旋转顺时针为正，逆时针为负。
        */
        /* note: Angle of this text((-180,180]). */
        virtual float GetAngle() = 0;
        /**
        * @par 说明
        * 文本角度，范围(-180,180]
        * @par 权限
        * 读写
        * @par 注解
        * 角度旋转顺时针为正，逆时针为负。
        */
        virtual void SetAngle(float fAngle) = 0;
        /**
        * @par 说明
        * 图形是否允许交互
        * @par 权限
        * 只读
        */
        virtual bool GetInteraction() const= 0;
        /**
        * @par 说明
        * 图形是否允许交互
        * @par 权限
        * 只读
        */
        virtual void SetInteraction(bool bInteraction) = 0;
        /**
        * @par 说明
        * 文本位置
        * @par 权限
        * 读写
        */
        /* note: Position of this text. */
        virtual MVD_TEXT_POSITION GetPosition() const = 0;
        /**
        * @par 说明
        * 文本位置
        * @par 权限
        * 读写
        */
        virtual void SetPosition(MVD_TEXT_POSITION stPosition) = 0;
    };
    /* Class that represents a rectangle. */
    class IMvdRectangleF : public IMvdShape,public IMvdShapeEx
    {
    //Constructor and Destructor
    protected:
        explicit IMvdRectangleF() {}
        explicit IMvdRectangleF(float fCenterX, float fCenterY, float fWidth, float fHeight) {}
        virtual ~IMvdRectangleF() {}

    public:
        virtual IMvdRectangleF& operator=(const IMvdShape& refShape) { return *this; }
        virtual IMvdRectangleF& operator=(const IMvdRectangleF& refRect) { return *this; }
        virtual bool operator==(IMvdShape const& refShape) { return false; }
        virtual bool operator==(IMvdRectangleF const& refRect) { return false; }

    // Clone methods
    public:
        /**
         * @brief 克隆矩形描述类对象
         * @param 无
         * @return 成功，返回矩形描述类对象;失败，抛出异常。
         * @par 注解
         * 
         */
        /* Returns a deep copy of this class instance. Derived classes that implement 
           Clone should override this method. Other clients who wish to clone this instance 
            should call IMvdRectangleF.Clone.*/
        virtual IMvdRectangleF* Clone() = 0;

    //properties
    public:
        MVD_SHAPE_TYPE GetShapeType() const {return MvdShapeRectangle;}
         /**
         * @par 说明
         * 矩形中心X坐标
         * @par 权限
         * 读写
         */
        /* note: Center X coordinate of this rectangle. */
        virtual float GetCenterX() const = 0;
         /**
         * @par 说明
         * 矩形中心X坐标
         * @par 权限
         * 读写
         */
        virtual void SetCenterX(float fCenterX) = 0;
         /**
         * @par 说明
         * 矩形中心Y坐标
         * @par 权限
         * 读写
         */
        /* note: Center Y coordinate of this rectangle. */
        virtual float GetCenterY() const = 0;
         /**
         * @par 说明
         * 矩形中心Y坐标
         * @par 权限
         * 读写
         */
        virtual void SetCenterY(float fCenterY) = 0;
         /**
         * @par 说明
         * 矩形宽度
         * @par 权限
         * 读写
         */
        /* note: Width of this rectangle. */
        virtual float GetWidth() const = 0;
         /**
         * @par 说明
         * 矩形宽度
         * @par 权限
         * 读写
         */
        virtual void SetWidth(float fWidth) = 0;
         /**
         * @par 说明
         * 矩形高度
         * @par 权限
         * 读写
         */
        /* note: Height of this rectangle. */
        virtual float GetHeight() const = 0;
         /**
         * @par 说明
         * 矩形高度
         * @par 权限
         * 读写
         */
        virtual void SetHeight(float fHeight) = 0;
         /**
         * @par 说明
         * 矩形角度，范围(-180,180]
         * @par 权限
         * 读写
         * @par 注解
         * 角度旋转顺时针为正，逆时针为负。
         */
        /* note: Angle of this rectangle((-180,180]). */
        virtual float GetAngle() = 0;
         /**
         * @par 说明
         * 矩形角度，范围(-180,180]
         * @par 权限
         * 读写
         * @par 注解
         * 角度旋转顺时针为正，逆时针为负。
         */
        virtual void SetAngle(float fAngle) = 0;

    // methods
         /**
         * @par 说明
         * 矩形最小的X坐标
         * @par 权限
         * 读写
         */
        /* note: Minimum X coordinate of this rectangle. */
        virtual float GetMinimumX() = 0;
         /**
         * @par 说明
         * 矩形最小的Y坐标
         * @par 权限
         * 读写
         */
        virtual float GetMinimumY() = 0;
         /**
         * @par 说明
         * 矩形左上角点的X坐标
         * @par 权限
         * 读写
         */
        /* note: X coordinate of the left-top vertex this rectangle. */
        virtual float GetLeftTopX() = 0;
         /**
         * @par 说明
         * 矩形左上角点的Y坐标
         * @par 权限
         * 读写
         */
         /* note: Y coordinate of the left-top vertex this rectangle. */
        virtual float GetLeftTopY() = 0;
        /**
         * @par 说明
         * 图形是否允许交互
         * @par 权限
         * 只读
         */
        virtual bool GetInteraction() = 0;
        /**
         * @par 说明
         * 图形是否允许交互
         * @par 权限
         * 只读
         */
        virtual void SetInteraction(bool bInteraction) = 0;
    };
    
    /* Class that represents a circle. */
    class IMvdCircleF : public IMvdShape,public IMvdShapeEx
    {
    //Constructor and Destructor
    protected:
        explicit IMvdCircleF() {}
        explicit IMvdCircleF(MVD_POINT_F stCenter, float fRadius) {}
        virtual ~IMvdCircleF() {}

    public:
        virtual IMvdCircleF& operator=(const IMvdShape& refShape) { return *this; }
        virtual IMvdCircleF& operator=(const IMvdCircleF& refCircle) { return *this; }
        virtual bool operator==(IMvdShape const& refShape) { return false; }
        virtual bool operator==(IMvdCircleF const& refCircle) { return false; }

    // Clone methods
    public:
        /**
         * @brief 克隆矩形描述类
         * @param 无
         * @return 成功，返回圆形描述类信息;失败，抛出异常。
         * @par 注解
         * 希望克隆此实例的其他客户端调用IMvdCircleF.Clone。
         */
        /* Returns a deep copy of this class instance. Derived classes that implement 
         Clone should override this method. Other clients who wish to clone this instance 
         should call IMvdCircleF.Clone.*/
        virtual IMvdCircleF* Clone() = 0;

    //properties
    public:
        MVD_SHAPE_TYPE GetShapeType() const {return MvdShapeCircle;}
         /**
         * @par 说明
         * 圆心
         * @par 权限
         * 读写
         */
        /* note: Get center coordinate of this circle. */
        virtual MVD_POINT_F GetCenter() const = 0;
         /**
         * @par 说明
         * 圆心
         * @par 权限
         * 读写
         */
        virtual void SetCenter(MVD_POINT_F stCenter) = 0;
         /**
         * @par 说明
         * 半径
         * @par 权限
         * 读写
         */
        /* note: Get radius of this circle. */
        virtual float GetRadius() const = 0;
         /**
         * @par 说明
         * 半径
         * @par 权限
         * 读写
         */
        virtual void SetRadius(float fRadius) = 0;
        /**
         * @par 说明
         * 图形是否允许交互
         * @par 权限
         * 只读
         */
        virtual bool GetInteraction() = 0;
        /**
         * @par 说明
         * 图形是否允许交互
         * @par 权限
         * 只读
         */
        virtual void SetInteraction(bool bInteraction) = 0;
    };

    /* Class that represents a annular sector. */
    class IMvdAnnularSectorF : public IMvdShape,public IMvdShapeEx
    {
    //Constructor and Destructor
    protected:
        explicit IMvdAnnularSectorF() {}
        explicit IMvdAnnularSectorF(MVD_POINT_F stCenter, float fInnerRadius, float fOuterRadius, float fStartAngle, float fAngleRange) {}
        virtual ~IMvdAnnularSectorF() {}

    public:
        virtual IMvdAnnularSectorF& operator=(const IMvdShape& refShape) { return *this; }
        virtual IMvdAnnularSectorF& operator=(const IMvdAnnularSectorF& refAnnul) { return *this; }
        virtual bool operator==(IMvdShape const& refShape) { return false; }
        virtual bool operator==(IMvdAnnularSectorF const& refAnnul) { return false; }

    //Clone methods
    public:
        /**
         * @brief 克隆圆环描述类
         * @param 无
         * @return 成功，返回圆环描述类信息;失败，抛出异常。
         * @par 注解
         * 深拷贝一份当前类
         */
        /* Returns a deep copy of this class instance. Derived classes that implement 
           Clone should override this method. Other clients who wish to clone this instance 
            should call IMvdAnnularSectorF.Clone.*/
        virtual IMvdAnnularSectorF* Clone() = 0;

    //properties
    public:
        MVD_SHAPE_TYPE GetShapeType() const {return MvdShapeAnnularSector;}
         /**
         * @par 说明
         * 圆环中心
         * @par 权限
         * 读写
         */
        /* note: Get center coordinate of this annular sector. */
        virtual MVD_POINT_F GetCenter() const = 0;
         /**
         * @par 说明
         * 圆环中心
         * @par 权限
         * 读写
         */
        virtual void SetCenter(MVD_POINT_F stCenter) = 0;
         /**
         * @par 说明
         * 圆环内半径
         * @par 权限
         * 读写
         */
        /* note: Get inner radius of this annular sector. */
        virtual float GetInnerRadius() const = 0;
         /**
         * @par 说明
         * 圆环内半径
         * @par 权限
         * 读写
         */
        virtual void SetInnerRadius(float fInnerRadius) = 0;
         /**
         * @par 说明
         * 圆环外半径
         * @par 权限
         * 读写
         */
        /* note: Get outer radius of this annular sector. */
        virtual float GetOuterRadius() const = 0;
         /**
         * @par 说明
         * 圆环外半径
         * @par 权限
         * 读写
         */
        virtual void SetOuterRadius(float fOuterRadius) = 0;
         /**
         * @par 说明
         * 起始角度，范围为(-180,180] 
         * @par 权限
         * 读写
         */
        /* note: Get start angle of this annular sector(-180,180]. */
        virtual float GetStartAngle() const = 0;
         /**
         * @par 说明
         * 起始角度，范围为(-180,180] 
         * @par 权限
         * 读写
         */
        virtual void SetStartAngle(float fStartAngle) = 0;
         /**
         * @par 说明
         * 角度范围，范围为(0,360]
         * @par 权限
         * 读写
         */
        /* note: Get the angle range of this annular sector(0, 360]. */
        virtual float GetAngleRange() const = 0;
         /**
         * @par 说明
         * 角度范围，范围为(0,360]
         * @par 权限
         * 读写
         */
        virtual void SetAngleRange(float fAngleRange) = 0;
        /**
         * @par 说明
         * 图形是否允许交互
         * @par 权限
         * 只读
         */
        virtual bool GetInteraction() = 0;
        /**
         * @par 说明
         * 图形是否允许交互
         * @par 权限
         * 只读
         */
        virtual void SetInteraction(bool bInteraction) = 0;
    };

    /* Class that represents a parallelogram. */
    class IMvdParallelogramF : public IMvdShape,public IMvdShapeEx
    {
    //Constructor and Destructor
    protected:
        explicit IMvdParallelogramF() {}
        explicit IMvdParallelogramF(MVD_POINT_F stCenter, float fWSide, float fHSide, float fSkewAngle) {}
        virtual ~IMvdParallelogramF() {}

    public:
        virtual IMvdParallelogramF& operator=(const IMvdShape& refShape) { return *this; }
        virtual IMvdParallelogramF& operator=(const IMvdParallelogramF& refParal) { return *this; }
        virtual bool operator==(IMvdShape const& refShape) { return false; }
        virtual bool operator==(IMvdParallelogramF const& refParal) { return false; }

    // Clone methods
    public:
        /**
         * @brief 克隆平行四边形描述类
         * @param 无
         * @return 成功，返回平行四边形描述类信息;失败，抛出异常。
         * @par 注解
         * 深拷贝一份当前类
         */
        /* Returns a deep copy of this class instance. Derived classes that implement 
           Clone should override this method. Other clients who wish to clone this instance 
            should call IMvdParallelogramF.Clone.*/
        virtual IMvdParallelogramF* Clone() = 0;

    public:
        MVD_SHAPE_TYPE GetShapeType() const {return MvdShapeParallelogram;}
         /**
         * @par 说明
         * 平行四边形中心
         * @par 权限
         * 读写
         */
        /* note: Center coordinate of this parallelogram. */
        virtual MVD_POINT_F GetCenter() const = 0;
         /**
         * @par 说明
         * 平行四边形中心
         * @par 权限
         * 读写
         */
        virtual void SetCenter(MVD_POINT_F stCenter) = 0;
         /**
         * @par 说明
         * 平行四边形宽的长度
         * @par 权限
         * 读写
         */
        /* note: Side length in the width direction of this parallelogram. */
        virtual float GetWSide() const = 0;
         /**
         * @par 说明
         * 平行四边形宽的长度
         * @par 权限
         * 读写
         */
        virtual void SetWSide(float fWSide) = 0;
         /**
         * @par 说明
         * 平行四边形高的长度
         * @par 权限
         * 读写
         */
        /* note: Side length in the height direction of this parallelogram. */
        virtual float GetHSide() const = 0;
         /**
         * @par 说明
         * 平行四边形高的长度
         * @par 权限
         * 读写
         */
        virtual void SetHSide(float fHSide) = 0;
         /**
         * @par 说明
         * 平行四边形相对于高方向的倾斜程度，顺时针为正，逆时针为负，范围为[-90,90]
         * @par 权限
         * 读写
         */
        /* note: Skew angle of this parallelogram relative to the HSide direction([-90,90]). */
        virtual float GetSkewAngle() const = 0;
         /**
         * @par 说明
         * 平行四边形相对于高方向的倾斜程度，顺时针为正，逆时针为负，范围为[-90,90]
         * @par 权限
         * 读写
         */
        virtual void SetSkewAngle(float fSkewAngle) = 0;
         /**
         * @par 说明
         * 角度，范围为(-180,180]
         * @par 权限
         * 读写
         * @par 注解
         * 角度旋转顺时针为正，逆时针为负。
         */
        /* note: Angle of this parallelogram((-180,180]). */
        virtual float GetAngle() = 0;
         /**
         * @par 说明
         * 角度，范围为(-180,180]
         * @par 权限
         * 读写
         * @par 注解
         * 角度旋转顺时针为正，逆时针为负。
         */
        virtual void SetAngle(float fAngle) = 0;
        /**
         * @par 说明
         * 图形是否允许交互
         * @par 权限
         * 只读
         */
        virtual bool GetInteraction() = 0;
        /**
         * @par 说明
         * 图形是否允许交互
         * @par 权限
         * 只读
         */
        virtual void SetInteraction(bool bInteraction) = 0;
    };

    /* Class that represents a polygon consisting of multiple vertices. */
    class IMvdPolygonF : public IMvdShape,public IMvdShapeEx
    {
    //Constructor and Destructor
    protected:
        explicit IMvdPolygonF() {}
        virtual ~IMvdPolygonF() {}

    public:
        virtual IMvdPolygonF& operator=(const IMvdShape& refShape) { return *this; }
        virtual IMvdPolygonF& operator=(const IMvdPolygonF& refPoly) { return *this; }
        virtual bool operator==(IMvdShape const& refShape) { return false; }
        virtual bool operator==(IMvdPolygonF const& refPoly) { return false; }

    public:
        /**
         * @brief 克隆多边形描述类
         * @param 无
         * @return 成功，返回多边形描述类信息;失败，抛出异常。
         * @par 注解
         * 深拷贝一份当前类
         */
        /* Returns a deep copy of this class instance. Derived classes that implement 
        Clone should override this method. Other clients who wish to clone this instance 
        should call IMvdPolygonF.Clone.*/
        virtual IMvdPolygonF* Clone() = 0;

    public:
        MVD_SHAPE_TYPE GetShapeType() const {return MvdShapePolygon;}
         /**
         * @par 说明
         * 多边形顶点数，上限为32个
         * @par 权限
         * 只读
         */
        /* note: Get the number of vertices of this polygon. */
        virtual unsigned int GetVertexNum() = 0;
         /**
         * @par 说明
         * 添加顶点。如果使用默认索引-1，则新顶点将添加到任何现有顶点的末端；否则，索引范围为[0，VertexNum]
         */
        /* Add a vertex to the polygon. If the default index -1 is used, the new vertex will be added to the end of any existing vertices. 
         Otherwise Index must be >= 0 and <= VertexNum. Support up to 32 vertices.*/
        virtual void AddVertex(float fX, float fY, int nIndex = -1) = 0;
         /**
         * @par 说明
         * 根据索引获取顶点坐标，索引范围为[0，VertexNum）
         * @par 权限
         * 读写
         */
        /* Get the coordinates of the vertex at the specified index. Index must be >= 0 and < VertexNum. */
        virtual void GetVertex(int nIndex, float& fX, float& fY ) = 0;
         /**
         * @par 说明
         * 根据索引删除顶点，索引范围为[0，VertexNum）
         * @par 权限
         * 读写
         */
        /* Remove the specified vertex from the polygon. Index must be >= 0 and < VertexNum. */
        virtual void RemoveVertex(int nIndex) = 0;
         /**
         * @par 说明
         * 根据索引设置顶点坐标，索引范围为[0，VertexNum）
         */
        /* Set the coordinates of the vertex at the specified index. Index must be >= 0 and < VertexNum. */
        virtual void SetVertex(int nIndex, float fX, float fY) = 0;
        /**
         * @par 说明
         * 图形是否允许交互
         * @par 权限
         * 只读
         */
        virtual bool GetInteraction() = 0;
        /**
         * @par 说明
         * 图形是否允许交互
         * @par 权限
         * 只读
         */
        virtual void SetInteraction(bool bInteraction) = 0;
        /**
        * @par 说明
        * 清除所有顶点
        * @par 权限
        * 读写
        */
        virtual void ClearVertices() = 0;

    };

    /* Class that represents a set of multiple points. */
    class IMvdPointSetF : public IMvdShape,public IMvdShapeEx
    {
    //Constructor and Destructor
    protected:
        explicit IMvdPointSetF() {}
        virtual ~IMvdPointSetF() {}

    public:
        virtual IMvdPointSetF& operator=(const IMvdShape& refShape) { return *this; }
        virtual IMvdPointSetF& operator=(const IMvdPointSetF& refPtSet) { return *this; }
        virtual bool operator==(IMvdShape const& refShape) { return false; }
        virtual bool operator==(IMvdPointSetF const& refPtSet) { return false; }

    public:
        /**
         * @brief 克隆离散点集描述类
         * @param 无
         * @return 成功，返回离散点集描述类信息;失败，抛出异常。
         * @par 注解
         * 深拷贝一份当前类
         */
        /* Returns a deep copy of this class instance. Derived classes that implement 
        Clone should override this method. Other clients who wish to clone this instance 
        should call IMvdPointSetF.Clone.*/
        virtual IMvdPointSetF* Clone() = 0;

    //properties
    public:
        MVD_SHAPE_TYPE GetShapeType() const {return MvdShapePointSet;}
        /**
         * @par 说明
         * 点的数量
         * @par 权限
         * 只读
         */
        /* note: Get the number of points of this set. */
        virtual unsigned int GetPointsNum() = 0;
        /**
         * @par 说明
         * 集合内添加点。如果使用默认索引-1，则新点将添加到现有点的末端；否则，索引设置范围为[0,PointsNum]
         */
        /* Add a point to the set. If the default index -1 is used, the new point will be added to the end of any existing points. 
         Otherwise Index must be >= 0 and <= PointsNum. Support up to 10000 points. */
        virtual void AddPoint(float fX, float fY, int nIndex = -1) = 0;
        /**
         * @par 说明
         * 根据索引获取点坐标，索引的范围为[0,PointsNum）
         * @par 权限
         * 读写
         */
        /* Get the coordinates of the point at the specified index. Index must be >= 0 and < PointsNum. */
        virtual void GetPoint(int nIndex, float& fX, float& fY ) = 0;
        /**
         * @par 说明
         * 根据索引从集合中移除点，索引设置范围为[0,PointsNum）
         */
        /* Remove the specified point from the set. Index must be >= 0 and < PointsNum. */
        virtual void RemovePoint(int nIndex) = 0;
        /**
         * @par 说明
         * 根据索引设置点坐标，索引的范围为[0,PointsNum）
         * @par 权限
         * 读写
         */
        /* Set the coordinates of the point at the specified index. Index must be >= 0 and < PointsNum. */
        virtual void SetPoint(int nIndex, float fX, float fY) = 0;
        /**
         * @par 说明
         * 图形是否允许交互
         * @par 权限
         * 只读
         */
        virtual bool GetInteraction() = 0;
        /**
         * @par 说明
         * 图形是否允许交互
         * @par 权限
         * 只读
         */
        virtual void SetInteraction(bool bInteraction) = 0;
        /**
        * @par 说明
        * 清除所有顶点
        * @par 权限
        * 读写
        */
        virtual void ClearPoints() = 0;
    };

    /* Class that represents a polyline segment consisting of multiple turning points. */
    class IMvdPolylineSegmentF : public IMvdShape,public IMvdShapeEx
    {
    //Constructor and Destructor
    protected:
        explicit IMvdPolylineSegmentF() {}
        virtual ~IMvdPolylineSegmentF() {}
    public:
        virtual IMvdPolylineSegmentF& operator=(const IMvdShape& refShape) { return *this; }
        virtual IMvdPolylineSegmentF& operator=(const IMvdPolylineSegmentF& refPoly) { return *this; }
        virtual bool operator==(IMvdShape const& refShape) { return false; }
        virtual bool operator==(IMvdPolylineSegmentF const& refPoly) { return false; }

    public:
        /**
         * @brief 克隆折线段类实例
         * @param 无
         * @return 成功，返回折线段实例;失败，抛出异常。
         * @par 注解
         * 深拷贝一份当前类
         */
        /* Returns a deep copy of this class instance. Derived classes that implement 
        Clone should override this method. Other clients who wish to clone this instance 
        should call IMvdPolylineSegmentF.Clone.*/
        virtual IMvdPolylineSegmentF* Clone() = 0;

    //properties
    public:
        MVD_SHAPE_TYPE GetShapeType() const {return MvdShapePolylineSegment;}
         /**
         * @par 说明
         * 获取折线段顶点数
         * @par 权限
         * 只读
         */
        /* note: Get the number of vertices of this polyline. */
        virtual unsigned int GetVertexNum() = 0;
         /**
         * @par 说明
         * 添加顶点。如果使用默认索引-1，则新顶点将添加到任何现有顶点的末端；否则按照索引插入，索引范围为[0,VertexNum]
         */
        /* Add a vertex to this polyline. If the default index -1 is used, the new vertex will be added to the end of any existing vertices. 
         Otherwise Index must be >= 0 and <= SegmentsNum. Unlimited. */
        virtual void AddVertex(float fX, float fY, int nIndex = -1) = 0;
         /**
         * @par 说明
         * 根据索引获取顶点的坐标,索引范围为[0,VertexNum)
         */
        /* Get the coordinates of the vertex at the specified index. Index must be >= 0 and < VertexNum. */
        virtual void GetVertex(int nIndex, float& fX, float& fY ) = 0;
         /**
         * @par 说明
         * 根据索引移除指定顶点,索引范围为[0,VertexNum)
         * @par 权限
         * 读写
         */
        /* Remove the specified vertex from the polygon. Index must be >= 0 and < VertexNum. */
        virtual void RemoveVertex(int nIndex) = 0;
         /**
         * @par 说明
         * 根据索引更新指定顶点的坐标,索引范围为[0,VertexNum)
         * @par 权限
         * 读写
         */
        /* Set the coordinates of the vertex at the specified index. Index must be >= 0 and < VertexNum. */
        virtual void SetVertex(int nIndex, float fX, float fY) = 0;
        /**
         * @par 说明
         * 图形是否允许交互
         * @par 权限
         * 只读
         */
        virtual bool GetInteraction() = 0;
        /**
         * @par 说明
         * 图形是否允许交互
         * @par 权限
         * 只读
         */
        virtual void SetInteraction(bool bInteraction) = 0;
        /**
        * @par 说明
        * 清除所有顶点
        * @par 权限
        * 读写
        */
        virtual void ClearVertices() = 0;
    };
}


/*  note:Interfaces to export.  */
#ifdef __cplusplus
extern "C" {
#endif

    /* note: Create instance of IMvdLineSegmentF. */
    MVD_CPP_API int _stdcall CreateLineSegmentInstance(VisionDesigner::IMvdLineSegmentF** ppLineInstance, VisionDesigner::MVD_POINT_F stStartPoint, VisionDesigner::MVD_POINT_F stEndPoint);
    /* note: Destroy instance of IMvdLineSegmentF. */
    MVD_CPP_API int _stdcall DestroyLineSegmentInstance(VisionDesigner::IMvdLineSegmentF* pLineInstance);

    /* note: Create instance of IMvdRectangleF. */
    MVD_CPP_API int _stdcall CreateRectangleInstance(VisionDesigner::IMvdRectangleF** ppRectInstance, float fCenterX, float fCenterY, float fWidth, float fHeight);
    /* note: Destroy instance of IMvdRectangleF. */
    MVD_CPP_API int _stdcall DestroyRectangleInstance(VisionDesigner::IMvdRectangleF* pRectInstance);

    /* note: Create instance of IMvdCircleF. */
    MVD_CPP_API int _stdcall CreateCircleInstance(VisionDesigner::IMvdCircleF** ppCircleInstance, VisionDesigner::MVD_POINT_F stCenter, float fRadius);
    /* note: Destroy instance of IMvdCircleF. */
    MVD_CPP_API int _stdcall DestroyCircleInstance(VisionDesigner::IMvdCircleF* pCircleInstance);

    /* note: Create instance of IMvdAnnularSectorF. */
    MVD_CPP_API int _stdcall CreateAnnularSectorInstance(VisionDesigner::IMvdAnnularSectorF** ppAnnularSectorInstance, VisionDesigner::MVD_POINT_F stCenter, float fInnerRadius, float fOuterRadius, float fStartAngle, float fAngleRange);
    /* note: Destroy instance of IMvdAnnularSectorF. */
    MVD_CPP_API int _stdcall DestroyAnnularSectorInstance(VisionDesigner::IMvdAnnularSectorF* pAnnularSectorInstance);

    /* note: Create instance of IMvdParallelogramF. */
    MVD_CPP_API int _stdcall CreateParallelogramInstance(VisionDesigner::IMvdParallelogramF** ppParallelogramInstance, VisionDesigner::MVD_POINT_F stCenter, float fWSide, float fHSide, float fSkewAngle);
    /* note: Destroy instance of IMvdParallelogramF. */
    MVD_CPP_API int _stdcall DestroyParallelogramInstance(VisionDesigner::IMvdParallelogramF* pParallelogramInstance);

    /* note: Create instance of IMvdPolygonF. */
    MVD_CPP_API int _stdcall CreatePolygonInstance(VisionDesigner::IMvdPolygonF** ppPolygonInstance);
    /* note: Destroy instance of IMvdPolygonF. */
    MVD_CPP_API int _stdcall DestroyPolygonInstance(VisionDesigner::IMvdPolygonF* pPolygonInstance);

    /* note: Create instance of IMvdPointSetF. */
    MVD_CPP_API int _stdcall CreatePointSetInstance(VisionDesigner::IMvdPointSetF** ppPointSetInstance);
    /* note: Destroy instance of IMvdPointSetF. */
    MVD_CPP_API int _stdcall DestroyPointSetInstance(VisionDesigner::IMvdPointSetF* pPointSetInstance);

    /* note: Create instance of IMvdPolylineSegmentF. */
    MVD_CPP_API int _stdcall CreatePolylineSegmentInstance(VisionDesigner::IMvdPolylineSegmentF** ppPolylineInstance);
    /* note: Destroy instance of IMvdPolylineSegmentF. */
    MVD_CPP_API int _stdcall DestroyPolylineSegmentInstance(VisionDesigner::IMvdPolylineSegmentF* pPolylineInstance);

    /* note: Create instance of IMvdTextF. */
    MVD_CPP_API int _stdcall CreateTextInstance(VisionDesigner::IMvdTextF** ppTextInstance, float fCenterX, float fCenterY, const char pcContent[MVD_TEXT_CONTENT_MAX_LEN]);
    /* note: Destroy instance of IMvdTextF. */
    MVD_CPP_API int _stdcall DestroyTextInstance(VisionDesigner::IMvdTextF* pTextInstance);

    /* note: Create instance of IMvdTextF. */
    MVD_CPP_API int _stdcall CreateTextInstanceEx(VisionDesigner::IMvdTextF** ppTextInstance, float fX, float fY, VisionDesigner::MVD_TEXT_POSITION_TYPE enType, const char pcContent[MVD_TEXT_CONTENT_MAX_LEN]);
    /* note: Destroy instance of IMvdTextF. */
    MVD_CPP_API int _stdcall DestroyTextInstanceEx(VisionDesigner::IMvdTextF* pTextInstance);

    /* note: Destroy instance of IMvdShape. */
    MVD_CPP_API int _stdcall DestroyShapeInstance(VisionDesigner::IMvdShape* pShapeInstance);

#ifdef __cplusplus
}
#endif 


#endif    ///<_MVD_SHAPE_CPP_H_
