#include <windows.h>
#define WINDOW_CLASS_NAME TEXT("WisdomSoft.Sample.Window")

int WINAPI WinMain(
	HINSTANCE hInstance,      // ���݂̃C���X�^���X�̃n���h��
	HINSTANCE hPrevInstance,  // �ȑO�̃C���X�^���X�̃n���h��
	LPSTR lpCmdLine,          // �R�}���h���C��
	int nCmdShow              // �\�����
	)

{
	
	HWND hWnd;
	WNDCLASS wc;
	/*�E�B���h�E�N���X�̓o�^*/

	wc.style = CS_HREDRAW | CS_VREDRAW;/*�E�B���h�E���ĕ`��*/
	wc.lpfnWndProc = DefWindowProc;/*�E�B���h�E�̓������������֐��ւ̃|�C���^���w��*/
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_BACKGROUND + 1;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	
	/*typedef struct _WNDCLASS { 
    UINT    style; �N���X�X�^�C���萔
    WNDPROC lpfnWndProc; �E�B���h�E�v���V�[�W��
    int     cbClsExtra;  �ǉ��̈�
    int     cbWndExtra; �ǉ��̈�
    HANDLE  hInstance; �C���X�^���X�n���h�����w��
    HICON   hIcon; �E�B���h�E�̃A�C�R����ݒ�
    HCURSOR hCursor; ���݂̃}�E�X�J�[�\��
    HBRUSH  hbrBackground; �E�B���h�E�̃N���C�A���g�̈�h��Ԃ�
    LPCTSTR lpszMenuName; �f�t�H���g���j���[�ƂȂ郁�j���[�̖��O���w��
    LPCTSTR lpszClassName; ���̍\���̂Ɋ��蓖�Ă��ӂȃN���X�����w��
} WNDCLASS;*/

	if (!RegisterClass(&wc))/*RegisterClass() �֐��� WNDCLASS �\���̂ւ̃|�C���^��n��*/
	{
		MessageBox(NULL, TEXT("�E�B���h�E�N���X�̍쐬�Ɏ��s���܂���"), NULL, MB_OK);
		return 0;
	}

	/*�o�^�����N���X�̃E�B���h�E�𐶐�*/
	hWnd = CreateWindow(
		WINDOW_CLASS_NAME, TEXT("Window Title"),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		100, 100, 400, 300,
		NULL, NULL, hInstance, NULL
		);
	
	/*HWND CreateWindow(
  LPCTSTR lpClassName	�E�B���h�E�N���X��, LPCTSTR lpWindowName	�E�B���h�E�̃e�L�X�g,
  DWORD dwStyle,�E�B���h�E�X�^�C���萔
  int x, int y, int nWidth, int nHeight,
  HWND hWndParent	�q�E�B���h�E�𐶐�, HMENU hMenu	���j���[��ݒ�,
  HANDLE hInstance	�C���X�^���X�n���h�����w��, LPVOID lpParam	�f�[�^��n����i
);*/

	if (hWnd)
	{
		MessageBox(hWnd, TEXT("�E�B���h�E����������܂���"), TEXT("���"), MB_OK);
	}
	else
	{
		MessageBox(NULL, TEXT("�E�B���h�E�̐����Ɏ��s���܂���"), NULL, MB_OK | MB_ICONERROR);
	}
	
	return 0;
	
	/*int MessageBox(
		HWND hWnd,	�E�B���h�E�n���h��
		LPCTSTR lpText,	���b�Z�[�W�{�b�N�X�ɕ\������e�L�X�g�ƂȂ镶����
		LPCTSTR lpCaption,�_�C�A���O�̃^�C�g���o�[�ɕ\������镶����
		UINT uType	���b�Z�[�W�{�b�N�X�̎�ނ�\�� MB_ ����n�܂�萔�̃t���O(bottun)
		);*/
	
}