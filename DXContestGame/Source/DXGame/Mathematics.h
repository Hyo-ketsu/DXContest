#ifndef ____MATHEMATICS_H____
#define ____MATHEMATICS_H____


// ���쐔�w�֐�
namespace Mathematics {
    // �����
    struct LineInfo {
        DirectX::XMFLOAT3 startPos;     // �n�_
        DirectX::XMFLOAT3 endPos;       // �I�_
        DirectX::XMVECTOR direction;    // ���̌����̃x�N�g��
    };


    // �n�_�ƏI�_��ݒ肷�邱�ƂŐ��̏��𐶐�����N���X
    class LineInfoClass {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �n�_
        // @ Arg2 : �I�_
        LineInfoClass(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end);


        // �����Q�b�^�[
        LineInfo GetLineInfo(void) const { return m_lineInfo; }


        // ������o�^����
        // @ Ret  : �����
        // @ Arg1 : �n�_
        // @ Arg2 : �I�_
        LineInfo CreateLineInfo(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end);

    private:
        LineInfo m_lineInfo;    // ���̏��
    };
}


// ���쐔�w�֐�
namespace Mathematics { 
    // �_���猩�����̍ł��߂��ꏊ���v�Z����
    // @ Ret  : ���W
    // @ Arg1 : �_�̍��W
    // @ Arg2 : ���̏��
    DirectX::XMFLOAT3 PointToLineNear(const DirectX::XMFLOAT3& point, const Mathematics::LineInfoClass& line);
}


#endif // !____MATHEMATICS_H____
