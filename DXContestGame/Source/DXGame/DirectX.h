#ifndef __DIRECTX_H__
#define __DIRECTX_H__


// Device���擾����
// @ Ret  : Device
ID3D11Device* GetDevice(void);
// Context���擾����
// @ Ret  ; Context
ID3D11DeviceContext* GetContext(void);
// SwapChain���擾����
// @ Ret  : SwapChain
IDXGISwapChain* GetSwapChain(void);


// DirectX������������
// @ Ret  : ����������
// @ Arg1 : �E�B���h�E�n���h��
// @ Arg2 : �E�B���h�E���T�C�Y
// @ Arg3 : �E�B���h�E�c�T�C�Y
// @ Arg4 : �t���X�N���[����
const HRESULT InitDX(HWND hWnd, const UINT width, const UINT height, const bool isFullscreen);


// DirectX���I������
void UninitDX(void);


// �`��O����
void BeginDrawDX(void);
// �`��㏈��
void EndDrawDX(void);


// �[�x�o�b�t�@��L���ɂ��邩
void EnableDepth(const bool isEnable);

#endif // __DIRECTX_H__