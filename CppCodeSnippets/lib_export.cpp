#include "lib_export.hpp"

#define LIB_NAME_API __declspec(dllexport) // 将该宏定义在.cpp中做预处理

namespace ProjectName { namespace ModuleName {
class LIB_NAME_API RenderGraphicsImageImpl : public RenderGraphicsImage
{
public:
    /**
    * @brief 函数功能简述
    *
    * @param x 参数说明, 输入/输出参数, 表达含义, 是否有范围/限制等说明
    * @param y
    * @return void 返回值说明, 一般可能是 bool, 表示操作是否正常处理(error_no)
    * @note
    */
    void AddLines(int x, int y) override;
    void AddRects(int x, int y) override;
    void AddCircles(int x, int y) override;
    void SetName(const std::string &name) override;
    void SetName(std::string_view name) override;
    void SetImage(void *image) override;

private:
    std::string m_name;
    int         m_x;
    int         m_y;
    void       *m_image;

private:
    void getRenderColor();
    void getRenderSize();
};

// maybe you need some global function, not in the class and external, 'static'
static int scaleXcoordinate(int scale, int x)
{
    return x * scale;
}

static int scaleYcoordinate(int scale, int y)
{
    return y * scale;
}

// maybe you need some Struct data, not in the class and external
class UserData
{
public:
    UserData(void *_img)
        : mImg(_img) {};

    void *mImg;
    int   mColor;
    int   mThickness;
    int   mLine_type;
    float mOldP;
    float mCtoL;
    float mPts;
};

// Implementation of encapsulating and masking abstract interfaces
void RenderGraphicsImageImpl::AddLines(int x, int y) {}

void RenderGraphicsImageImpl::AddRects(int x, int y) {}

void RenderGraphicsImageImpl::AddCircles(int x, int y) {}

void RenderGraphicsImageImpl::SetName(const std::string &name) {}

void RenderGraphicsImageImpl::SetName(std::string_view name) {}

void RenderGraphicsImageImpl::SetImage(void *image) {}

/**
         * @brief Create 'RenderGraphicsImage' Instance
         * The function createSaveRenderImage create instance to render graphics into image.
         * The supported graphics see in 'RenderGraphics.hpp'
         * @return std::shared_ptr<RenderGraphicsImage>
         */
LIB_NAME_API std::shared_ptr<RenderGraphicsImage> CLAAING_CONVERTIONS createRenderGraphicsImage()
{
    return std::shared_ptr<RenderGraphicsImage>(new RenderGraphicsImageImpl());
}

}} // namespace ProjectName::ModuleName
