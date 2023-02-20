#ifndef HONEY_VECTOR_H
#define HONEY_VECTOR_H

#include <lua.h>


extern const char *nvg_ctx_tname;
extern const char *nvg_color_tname;
extern const char *nvg_paint_tname;


#define NVG_FUNCTIONS \
	/* context */ \
	X("CreateContext", nvgCreateContext_bind) \
	X("DeleteContext", nvgDeleteContext_bind) \
 \
	/* frame control */ \
	X("BeginFrame", nvgBeginFrame_bind) \
	X("CancelFrame", nvgCancelFrame_bind) \
	X("EndFrame", nvgEndFrame_bind) \
 \
	/* composite operation */ \
	X("GlobalCompositeOperation", nvgGlobalCompositeOperation_bind) \
	X("GlobalCompositeBlendFunc", nvgGlobalCompositeBlendFunc_bind) \
	X("GlobalCompositeBlendFuncSeparate", nvgGlobalCompositeBlendFuncSeparate_bind) \
 \
	/* color utils */ \
	X("RGB", nvgRGB_bind) \
	X("RGBf", nvgRGBf_bind) \
	X("RGBA", nvgRGBA_bind) \
	X("RGBAf", nvgRGBAf_bind) \
	X("LerpRGBA", nvgLerpRGBA_bind) \
	X("TransRGBA", nvgTransRGBA_bind) \
	X("TransRGBAf", nvgTransRGBAf_bind) \
	X("HSL", nvgHSL_bind) \
	X("HSLA", nvgHSLA_bind) \
 \
	/* state handling */ \
	X("Save", nvgSave_bind) \
	X("Restore", nvgRestore_bind) \
	X("Reset", nvgReset_bind) \
 \
	/* render styles */ \
	X("ShapeAntiAlias", nvgShapeAntiAlias_bind) \
	X("StrokeColor", nvgStrokeColor_bind) \
	X("StrokePaint", nvgStrokePaint_bind) \
	X("FillColor", nvgFillColor_bind) \
	X("FillPaint", nvgFillPaint_bind) \
	X("MiterLimit", nvgMiterLimit_bind) \
	X("StrokeWidth", nvgStrokeWidth_bind) \
	X("LineCap", nvgLineCap_bind) \
	X("LineJoin", nvgLineJoin_bind) \
	X("GlobalAlpha", nvgGlobalAlpha_bind) \
 \
	/* transforms */ \
	X("ResetTransform", nvgResetTransform_bind) \
	X("Transform", nvgTransform_bind) \
	X("Translate", nvgTranslate_bind) \
	X("Rotate", nvgRotate_bind) \
	X("SkewX", nvgSkewX_bind) \
	X("SkewY", nvgSkewY_bind) \
	X("Scale", nvgScale_bind) \
	X("CurrentTransform", nvgCurrentTransform_bind) \
	/* X("TransformIdentity", nvgTransformIdentity_bind) */ \
	/* X("TransformTranslate", nvgTransformTranslate_bind) */ \
	/* X("TransformScale", nvgTransformScale_bind) */ \
	/* X("TransformRotate", nvgTransformRotate_bind) */ \
	/* X("TransformSkewX", nvgTransformSkewX_bind) */ \
	/* X("TransformSkewY", nvgTransformSkewY_bind) */ \
	/* X("TransformMultiply", nvgTransformMultiply_bind) */ \
	/* X("TransformPremultiply", nvgTransformPremultiply_bind) */ \
	/* X("TransformInverse", nvgTransformInverse_bind) */ \
	/* X("TransformPoint", nvgTransformPoint_bind) */ \
 \
	/* images */ \
	X("CreateImage", nvgCreateImage_bind) \
	/* X("CreateImageMem", nvgCreateImageMem_bind) */ \
	/* X("CreateImageRGBA", nvgCreateImageRGBA_bind) */ \
	/* X("UpdateImage", nvgUpdateImage_bind) */ \
	X("ImageSize", nvgImageSize_bind) \
	X("DeleteImage", nvgDeleteImage_bind) \
 \
	/* paints */ \
	X("LinearGradient", nvgLinearGradient_bind) \
	X("BoxGradient", nvgBoxGradient_bind) \
	X("RadialGradient", nvgRadialGradient_bind) \
	X("ImagePattern", nvgImagePattern_bind) \
 \
	/* scissoring */ \
	X("Scissor", nvgScissor_bind) \
	X("IntersectScissor", nvgIntersectScissor_bind) \
	X("ResetScissor", nvgResetScissor_bind) \
 \
	/* paths */ \
	X("BeginPath", nvgBeginPath_bind) \
	X("MoveTo", nvgMoveTo_bind) \
	X("LineTo", nvgLineTo_bind) \
	X("BezierTo", nvgBezierTo_bind) \
	X("QuadTo", nvgQuadTo_bind) \
	X("ArcTo", nvgArcTo_bind) \
	X("ClosePath", nvgClosePath_bind) \
	X("PathWinding", nvgPathWinding_bind) \
	X("Arc", nvgArc_bind) \
	X("Rect", nvgRect_bind) \
	X("RoundedRect", nvgRoundedRect_bind) \
	X("RoundedRectVarying", nvgRoundedRectVarying_bind) \
	X("Ellipse", nvgEllipse_bind) \
	X("Circle", nvgCircle_bind) \
	X("Fill", nvgFill_bind) \
	X("Stroke", nvgStroke_bind) \
 \
	/* text */ \
	X("CreateFont", nvgCreateFont_bind) \
	X("CreateFontAtIndex", nvgCreateFontAtIndex_bind) \
	/* X("CreateFontMem", nvgCreateFontMem_bind) */ \
	/* X("CreateFontMemAtIndex", nvgCreateFontMemAtIndex_bind) */ \
	X("FindFont", nvgFindFont_bind) \
	X("AddFallbackFontId", nvgAddFallbackFontId_bind) \
	X("AddFallbackFont", nvgAddFallbackFont_bind) \
	X("ResetFallbackFontsId", nvgResetFallbackFontsId_bind) \
	X("ResetFallbackFonts", nvgResetFallbackFonts_bind) \
	X("FontSize", nvgFontSize_bind) \
	X("FontBlur", nvgFontBlur_bind) \
	X("TextLetterSpacing", nvgTextLetterSpacing_bind) \
	X("TextLineHeight", nvgTextLineHeight_bind) \
	X("TextAlign", nvgTextAlign_bind) \
	X("FontFaceId", nvgFontFaceId_bind) \
	X("FontFace", nvgFontFace_bind) \
	X("Text", nvgText_bind) \
	X("TextBox", nvgTextBox_bind) \
	X("TextBounds", nvgTextBounds_bind) \
	X("TextBoxBounds", nvgTextBoxBounds_bind) \
	/* X("TextGlyphPositions", nvgTextGlyphPositions_bind) */ \
	/* X("TextMetrics", nvgTextMetrics_bind) */ \
	/* X("TextBreakLines", nvgTextBreakLines_bind) */ \

	
/* function declarations */
#define X(unused, name) int name(lua_State *L);
NVG_FUNCTIONS
#undef X

#endif
