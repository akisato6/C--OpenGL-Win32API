#pragma once

#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )
#pragma comment( lib, "gdi32.lib" )
#pragma comment( lib, "User32.lib" )

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>


//↑こいつの#include は、たぶんこことかではなく、
// コードの中でもusing namespace System;とか記述する
// よりも前にしないと、C2872 に苦しめられることになる。

public ref class OpenGLSimpleAdapter
// ↑CLRでやる場合は、class の前に、public ref を入れてね
{
	//
	// OpenGL Simple Adaptor loOGLHost (C) 2008 nurs
	//
	// 使い方：
	// 1)本クラスのインスタンスを、ターゲットビューのメンバとして作成する。
	//   コンストラクタのHDCは、Win32なら
	//   　⇒  ::GetDC( this->GetSafeHwnd() ) );
	//   CLRのFormなら、
	//     ⇒　::GetDC( (HWND)parentForm->Handle.ToPointer() );
	//   などとして取ってきます。
	// 2)ターゲットビューの、適切な箇所（初期化、描画、リサイズ）にて、
	//   本ホストの、BeginRender()と、EndRender() を呼び出し、その間に、
	//   目的のOpenGL描画コードを記述します。
	// *)ちなみに利用側コードのどこかのcpp内にて、
	//#pragma comment( lib, "opengl32.lib" )
	//#pragma comment( lib, "glu32.lib" )
	//#pragma comment( lib, "gdi32.lib" )
	//#pragma comment( lib, "User32.lib" )
	// 　の記述も、忘れないで下さい。
	//
	// ★RenderPolicyを予め作成しておき、必要なときに必要な描画
	//   ポリシーで、Render() をかける、という使い方もできます。
	// ★注意：WindowsForm、.NET環境の場合は、プロジェクトの共通言語
	//   ランタイムサポートを、/clr:pure ではなく、/clr にする。
	//
	//
public:
	OpenGLSimpleAdapter(HDC dc){
		if (dc == 0) return;
		m_hdc = dc;
		{
			static PIXELFORMATDESCRIPTOR pfd = {
				sizeof(PIXELFORMATDESCRIPTOR), 1,
				PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
				PFD_DOUBLEBUFFER, PFD_TYPE_RGBA,
				32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				16, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0
			};
			GLint iPixelFormat;
			if ((iPixelFormat = ChoosePixelFormat(m_hdc, &pfd)) == 0)
				return;
			if (SetPixelFormat(m_hdc, iPixelFormat, &pfd) == FALSE)
				return;
		}
		if ((m_hglrc = wglCreateContext(m_hdc)) == 0)
			return; // pure Managed だとランタイムでエラーに
		if ((wglMakeCurrent(m_hdc, m_hglrc)) == 0)
			return;
		wglMakeCurrent(0, 0);
		return;
	}
	~OpenGLSimpleAdapter(void){}
	template< class RenderPolicy > void Render(RenderPolicy& po){
		wglMakeCurrent(this->m_hdc, this->m_hglrc);
		po();
		wglMakeCurrent(this->m_hdc, 0);
		SwapBuffers(this->m_hdc);
	}
	HDC BeginRender(void){
		wglMakeCurrent(this->m_hdc, this->m_hglrc);
		return this->m_hdc;
	}
	void EndRender(void){
		wglMakeCurrent(this->m_hdc, 0);
		SwapBuffers(this->m_hdc);
	}
	void EndRenderNoSwap(void){
		wglMakeCurrent(this->m_hdc, 0);
	}
private:
	HDC m_hdc;
	HGLRC m_hglrc;
};

/*使用例
まず、OpenGLSimpleAdapterのインスタンスを作成します。
そして、BeginRender() と、EndRender() の間に目的のOpenGLのgl描画コードを書きます。

private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
　GLAdapter =
 　　gcnew OpenGLSimpleAdapter(GetDC( (HWND)panel1->Handle.ToPointer() ));
   }
   private: System::Void panel1_Paint(System::Object^ sender,
   　　　　　　　　　　　　　　　　　 System::Windows::Forms::PaintEventArgs^  e) {
					 　GLAdapter->BeginRender();
					  　{
					   glClearColor( 0,0,0,0 );
					   glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
					   　}
						　GLAdapter->EndRender();
						 }
						 */
