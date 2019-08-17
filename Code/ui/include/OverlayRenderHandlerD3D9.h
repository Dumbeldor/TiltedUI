#pragma once

#include <OverlayRenderHandler.h>
#include <Meta.h>
#include <Signal.h>
#include <wrl.h>

struct IDirect3DTexture9;
struct IDirect3DDevice9;
struct ID3DXSprite;

struct OverlayRenderHandlerD3D9 : OverlayRenderHandler
{
    struct Renderer
    {
        Renderer() = default;
        virtual ~Renderer() = default;
        [[nodiscard]] virtual IDirect3DDevice9* GetDevice() const noexcept = 0;

        TP_NOCOPYMOVE(Renderer);
    };

    explicit OverlayRenderHandlerD3D9(Renderer* apRenderer) noexcept;
    virtual ~OverlayRenderHandlerD3D9();

    TP_NOCOPYMOVE(OverlayRenderHandlerD3D9);

    void Create() override;
    void Render() override;
    void Reset() override;

    void GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect) override;
    void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList& dirtyRects, const void* buffer, int width, int height) override;

    IMPLEMENT_REFCOUNTING(OverlayRenderHandlerD3D9);

private:
    int m_width{ 0 };
    int m_height{ 0 };
    Microsoft::WRL::ComPtr<IDirect3DTexture9> m_pTexture;
    Microsoft::WRL::ComPtr<ID3DXSprite> m_pSprite;
    Renderer* m_pRenderer;
};
