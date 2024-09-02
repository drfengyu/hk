/***************************************************************************************************
* File:  MVD_ErrorDefine_Exp.h
* Note:  ch: 算法相关的状态码定义，仅用于SDK V3.1版本中。
         En: Algorithm-related status code definition in namespace VisionDesigner. Only for SDK 3.1 version.
*
* Version:  V3.1.0.0
****************************************************************************************************/


#ifndef _MVD_ERROR_DEFINE_EXP_H_
#define _MVD_ERROR_DEFINE_EXP_H_

// 算法通用状态码:范围0x80100100-0x801001FF
const static int MVD_ALGORITHM_E_ALGORITHM_CPUID           = 0x80100100;    ///< ch: cpu不支持优化代码中的指令集 | en: CPU does not support optimizing instruction sets in code
const static int MVD_ALGORITHM_E_ALGORITHM_STEP            = 0x80100101;    ///< ch: 数据step不正确（除HKA_IMAGE结构体之外） | en: Wrong with the 'step' of data
const static int MVD_ALGORITHM_E_ALGORITHM_DATA_SIZE       = 0x80100102;    ///< ch: 数据大小不正确（一维数据len，二维数据的HKA_SIZE） | en: Incorrect length or size of data
const static int MVD_ALGORITHM_E_ALGORITHM_BAD_ARG         = 0x80100103;    ///< ch: 参数范围不正确 | en: Incorrect parameter range
const static int MVD_ALGORITHM_E_ALGORITHM_EXPIRE          = 0x80100104;    ///< ch: 算法库使用期限错误 | en: Error in limit of use of the Algorithmic Library
const static int MVD_ALGORITHM_E_ALGORITHM_ENCRYPT         = 0x80100105;    ///< ch: 加密错误 | en: Encryption error
const static int MVD_ALGORITHM_E_ALGORITHM_CALL_BACK       = 0x80100106;    ///< ch: 回调函数出错 | en: Wrong with the callback function
const static int MVD_ALGORITHM_E_ALGORITHM_OVER_MAX_MEM    = 0x80100107;    ///< ch: 超过HKA限定最大内存 | en: Exceeding the maximum memory limit
const static int MVD_ALGORITHM_E_ALGORITHM_NULL_PTR        = 0x80100108;    ///< ch: 函数参数指针为空（共用） | en: Empty function pointer is not allowed
const static int MVD_ALGORITHM_E_ALGORITHM_PARAM_NUM       = 0x80100109;    ///< ch: param_num参数不正确 | en: Incorrect name of the parameter
const static int MVD_ALGORITHM_E_ALGORITHM_PARAM_VALUE     = 0x8010010a;    ///< ch: value参数不正确或者超出范围 | en: Incorrect value of the parameter
const static int MVD_ALGORITHM_E_ALGORITHM_PARAM_INDEX     = 0x8010010b;    ///< ch: index参数不正确 | en: Incorrect index of the parameter
const static int MVD_ALGORITHM_E_ALGORITHM_FUNC_SIZE       = 0x8010010c;    ///< ch: 子处理时输入、输出参数大小不正确 | en: Incorrect size of I/O parameter for sub-processing
const static int MVD_ALGORITHM_E_ALGORITHM_FUNC_TYPE       = 0x8010010d;    ///< ch: 子处理类型不正确 | en: Incorrect sub-processing type
const static int MVD_ALGORITHM_E_ALGORITHM_PRC_SIZE        = 0x8010010e;    ///< ch: 处理时输入、输出参数大小不正确 | en: Incorrect size of I/O parameter for processing
const static int MVD_ALGORITHM_E_ALGORITHM_PRC_TYPE        = 0x8010010f;    ///< ch: 处理类型不正确 | en: Incorrect processing type
const static int MVD_ALGORITHM_E_ALGORITHM_CFG_SIZE        = 0x80100110;    ///< ch: 设置、获取参数输入、输出结构体大小不正确 | en: Incorrect size of the I/O structure for setting or getting parameter
const static int MVD_ALGORITHM_E_ALGORITHM_CFG_TYPE        = 0x80100111;    ///< ch: 设置、获取参数类型不正确 | en: Incorrect type of the I/O structure for setting or getting parameter
const static int MVD_ALGORITHM_E_ALGORITHM_IMG_DATA_NULL   = 0x80100112;    ///< ch: 图像数据存储地址为空（某个分量） | en: Empty address of the image data channel
const static int MVD_ALGORITHM_E_ALGORITHM_IMG_STEP        = 0x80100113;    ///< ch: 图像宽高与step参数不匹配（检测宽高和像素深度） | en: Mismatch between image width and height and 'step' parameters
const static int MVD_ALGORITHM_E_ALGORITHM_IMG_SIZE        = 0x80100114;    ///< ch: 图像宽高不正确或者超出范围 | en: Incorrect or out-of-range image width or height
const static int MVD_ALGORITHM_E_ALGORITHM_IMG_FORMAT      = 0x80100115;    ///< ch: 图像格式不正确或者不支持 | en: Incorrect or out-of-range pixel format
const static int MVD_ALGORITHM_E_ALGORITHM_MEM_ADDR_ALIGN  = 0x80100116;    ///< ch: 内存地址不满足对齐要求 | en: Memory address does not meet alignment requirements
const static int MVD_ALGORITHM_E_ALGORITHM_MEM_SIZE_ALIGN  = 0x80100117;    ///< ch: 内存空间大小不满足对齐要求 | en: Memory space size does not meet alignment requirements
const static int MVD_ALGORITHM_E_ALGORITHM_MEM_LACK        = 0x80100118;    ///< ch: 内存空间大小不够 | en: Insufficient memory space
const static int MVD_ALGORITHM_E_ALGORITHM_MEM_ALIGN       = 0x80100119;    ///< ch: 内存对齐不满足要求 | en: Memory alignment does not meet requirements
const static int MVD_ALGORITHM_E_ALGORITHM_MEM_NULL        = 0x8010011a;    ///< ch: 内存地址为空 | en: Empty address of the memory
const static int MVD_ALGORITHM_E_ALGORITHM_ABILITY_ARG     = 0x8010011b;    ///< ch: ABILITY存在无效参数(检查Init时的图像最大宽高) | en: Wrong with the algorithm ability(e.g. not supported)
const static int MVD_ALGORITHM_E_ALGORITHM_UNKNOW          = 0x8010011c;    ///< ch: 算法库未知错误 | en: Unknown Error in Algorithmic Library
const static int MVD_ALGORITHM_E_ALGORITHM_WARNING         = 0x8010011d;    ///< ch: 算法警告值 | en: Warning in Algorithmic Library

// 字符识别状态码:范围0x80100300-0x801003FF(其他预留)
const static int MVD_ALGORITHM_E_OCR_ROI_TOO_SMALL               = 0x80100301;    ///< ch: ROI区域比算法要求的最小宽高、模块要求的最小参数值小 | en: The ROI area is smaller than the minimum threshold required by the algorithm and the module.
const static int MVD_ALGORITHM_E_OCR_IMG_ABILITY_TOO_SMALL       = 0x80100302;    ///< ch: 图像能力集太小 | en: Beyond the limits of image ability.
const static int MVD_ALGORITHM_E_OCR_CHARACTER_ABILITY_TOO_SMALL = 0x80100303;    ///< ch: 字符能力集太小 | en: Beyond the limits of character ability.
const static int MVD_ALGORITHM_E_OCR_GENERATE_DATA_NUM           = 0x80100304;    ///< ch: 字库增加处理样本数量错误 | en: Font library failed to increase the number of samples.
const static int MVD_ALGORITHM_E_OCR_NO_FONT_FILE                = 0x80100305;    ///< ch: 字符识别处理缺失字库文件 | en: Character recognition processing failed because of missing font files.
const static int MVD_ALGORITHM_E_OCR_NO_TRAIN_DATA               = 0x80100306;    ///< ch: 字库训练处理缺失训练样本 | en: Font training failed because of missing training samples.
const static int MVD_ALGORITHM_E_OCR_TEXT_DETECT_OUT             = 0x80100307;    ///< ch: 文本检测区域的中心点不在图像内部 | en: The center point of the area to detect text is not inside the image.
const static int MVD_ALGORITHM_E_OCR_TEXT_BOX_INVALID            = 0x80100308;    ///< ch: 文本检测区域的高、宽小于算法支持的最小字符大小 | en: The width or height of the area to detect text is smaller than the minimum character size supported by the algorithm.
const static int MVD_ALGORITHM_E_OCR_FONT_MISMATCH               = 0x80100309;    ///< ch: 字库类型不匹配 | en: Font type does not match.
const static int MVD_ALGORITHM_E_OCR_FONT_NO_MATCHING_TYPE       = 0x80100310;    ///< ch: 字库没有与待识别字符类型一致的样本 | en: The font does not have a sample that matches the type of character to be recognized.
const static int MVD_ALGORITHM_E_OCR_EXCEED_MAX_LABEL_NUM        = 0x80100311;    ///< ch: 训练字符标签种类数大于上限 | en: 

// 字符缺陷检测状态码:范围0x80100400-0x801004FF(其他预留)
const static int MVD_ALGORITHM_E_MKINSP_PRC_TYPE_OR_MODU_ENABLE  = 0x80100401;    ///< ch: 输入处理类型与模块使能不一致 | en: Input processing type is inconsistent with the status of ModuleEnable
const static int MVD_ALGORITHM_E_MKINSP_MARK_NUM                 = 0x80100402;    ///< ch: 输入box个数小于MVBMKINSP_MARK_NUM_MIN或大于设置的最大个数 | en: The number of boxes input less than MVBMKINSP_MARK_NUM_MIN or greater than the maximum number set
const static int MVD_ALGORITHM_E_MKINSP_MARK_BOX_SCALE           = 0x80100403;    ///< ch: 输入字符box大小范围超过图像范围或与之前生成模型使用的mark_box大小不一样 | en: The input character box size range is larger than the image range or different from the mark_box size used in the previous generation model.
const static int MVD_ALGORITHM_E_MKINSP_PROC_ORDER               = 0x80100404;    ///< ch: proc_order输入异常 | en: Input exception
const static int MVD_ALGORITHM_E_MKINSP_MODEL_TYPE               = 0x80100405;    ///< ch: 模型输入类型不一致 | en: Model input type is inconsistent.
const static int MVD_ALGORITHM_E_MKINSP_MODEL_VERSION            = 0x80100406;    ///< ch: 模型输入版本不一致 | en: Model input version is inconsistent.
const static int MVD_ALGORITHM_E_MKINSP_MODEL_CONFIG             = 0x80100407;    ///< ch: 模型保存的参数异常 | en: Abnormal parameter saved by the model.

// 模板匹配状态码:范围0x80100500-0x801005FF(其他预留)
const static int MVD_ALGORITHM_E_PATMATCH_FEATURES_NOT_ENOUGH       = 0x80100501;    ///< ch: 特征不足：特征模板生成失败 | en: Failed to generate the feature modle
const static int MVD_ALGORITHM_E_PATMATCH_MATCH_TIME_OUT            = 0x80100502;    ///< ch: 算法超时：匹配时超出预定处理时间 | en: Exceeded the scheduled processing time when matching
const static int MVD_ALGORITHM_E_PATMATCH_MATCH_VERSION_ERROR       = 0x80100503;    ///< ch: 算法版本号出错：模板版本号与匹配版本不符 | en: Algorithm version error. The version of the feature modle does not match the version of Matching.
const static int MVD_ALGORITHM_E_PATMATCH_MODEL_VERSION_ERROR       = 0x80100504;    ///< ch: 模型版本号出错：模板版本号与当前版本不符 | en: Modle version error. The version of modle input does match the current version.
const static int MVD_ALGORITHM_E_PATMATCH_MALLOC_MODEL_BUFF_FAIL    = 0x80100505;    ///< ch: 建模时，模型内存申请失败 | en: Model memory allocation failed while modeling.


#endif //_MVD_ERROR_DEFINE_EXP_H_

