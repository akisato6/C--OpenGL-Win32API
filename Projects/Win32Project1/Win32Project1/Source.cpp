#include <windows.h>
#define WINDOW_CLASS_NAME TEXT("WisdomSoft.Sample.Window")

int WINAPI WinMain(
	HINSTANCE hInstance,      // 現在のインスタンスのハンドル
	HINSTANCE hPrevInstance,  // 以前のインスタンスのハンドル
	LPSTR lpCmdLine,          // コマンドライン
	int nCmdShow              // 表示状態
	)

{
	
	HWND hWnd;
	WNDCLASS wc;
	/*ウィンドウクラスの登録*/

	wc.style = CS_HREDRAW | CS_VREDRAW;/*ウィンドウを再描画*/
	wc.lpfnWndProc = DefWindowProc;/*ウィンドウの動作を処理する関数へのポインタを指定*/
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_BACKGROUND + 1;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	
	/*typedef struct _WNDCLASS { 
    UINT    style; クラススタイル定数
    WNDPROC lpfnWndProc; ウィンドウプロシージャ
    int     cbClsExtra;  追加領域
    int     cbWndExtra; 追加領域
    HANDLE  hInstance; インスタンスハンドルを指定
    HICON   hIcon; ウィンドウのアイコンを設定
    HCURSOR hCursor; 現在のマウスカーソル
    HBRUSH  hbrBackground; ウィンドウのクライアント領域塗りつぶす
    LPCTSTR lpszMenuName; デフォルトメニューとなるメニューの名前を指定
    LPCTSTR lpszClassName; この構造体に割り当てる一意なクラス名を指定
} WNDCLASS;*/

	if (!RegisterClass(&wc))/*RegisterClass() 関数に WNDCLASS 構造体へのポインタを渡す*/
	{
		MessageBox(NULL, TEXT("ウィンドウクラスの作成に失敗しました"), NULL, MB_OK);
		return 0;
	}

	/*登録したクラスのウィンドウを生成*/
	hWnd = CreateWindow(
		WINDOW_CLASS_NAME, TEXT("Window Title"),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		100, 100, 400, 300,
		NULL, NULL, hInstance, NULL
		);
	
	/*HWND CreateWindow(
  LPCTSTR lpClassName	ウィンドウクラス名, LPCTSTR lpWindowName	ウィンドウのテキスト,
  DWORD dwStyle,ウィンドウスタイル定数
  int x, int y, int nWidth, int nHeight,
  HWND hWndParent	子ウィンドウを生成, HMENU hMenu	メニューを設定,
  HANDLE hInstance	インスタンスハンドルを指定, LPVOID lpParam	データを渡す手段
);*/

	if (hWnd)
	{
		MessageBox(hWnd, TEXT("ウィンドウが生成されました"), TEXT("情報"), MB_OK);
	}
	else
	{
		MessageBox(NULL, TEXT("ウィンドウの生成に失敗しました"), NULL, MB_OK | MB_ICONERROR);
	}
	
	return 0;
	
	/*int MessageBox(
		HWND hWnd,	ウィンドウハンドル
		LPCTSTR lpText,	メッセージボックスに表示するテキストとなる文字列
		LPCTSTR lpCaption,ダイアログのタイトルバーに表示される文字列
		UINT uType	メッセージボックスの種類を表す MB_ から始まる定数のフラグ(bottun)
		);*/
	
}