#ifndef ____GENERICSINGLETON_H____
#define ____GENERICSINGLETON_H____

#include <memory>


// �V���O���g���p���ۃN���X
// @ Memo : ACSingleton ���t�����h�錾���Ă�������
// @ Memo : protected �� private �ŃR���X�g���N�^��錾���Ă�������
// @ Temp : �ԋp���邱�̃N���X�̃T�u�N���X
template<class T>
class Singleton {
public:
    // �C���X�^���X�̎擾
    // @ Ret  : ������Ȃ����Ƃ����m�ȃC���X�^���X
    static T* const Get(void);


    // �C���X�^���X�̖����I���
    static void DeleteInstance(void);

protected:
    // �R���X�g���N�^
    Singleton<T>(void) {}


    // �f�X�g���N�^
    virtual ~Singleton<T>(void) {}


private:
    static std::unique_ptr<T> ms_singleton; // �V���O���g���T�u�N���X

    Singleton(const Singleton &) = delete;
    Singleton& operator=(const Singleton &) = delete;
    Singleton(Singleton &&) = delete;
    Singleton& operator=(Singleton &&) = delete;
};


template <class T>
std::unique_ptr<T> Singleton<T>::ms_singleton;    // �V���O���g���T�u�N���X


template<class T>
T* const Singleton<T>::Get(void) {
    //----- �C���X�^���X�̐������f
    if (!(ms_singleton)) {
        //----- �C���X�^���X�����݂��Ȃ����ߐ���
        ms_singleton = std::unique_ptr<T>(new T());
    }

    //----- �C���X�^���X�̕ԋp
    return ms_singleton.get();
}


// �C���X�^���X�̖����I���
template<class T>
void Singleton<T>::DeleteInstance(void) {
    //----- �����I�J��
    ms_singleton.reset();
}


#endif // !define ____GENERICSINGLETON_H____
