#ifndef ____GENERICSINGLETON_H____
#define ____GENERICSINGLETON_H____

#include <mutex>
#include <memory>
#include <type_traits>


// �V���O���g���p���ۃN���X
// @ Memo : ACSingleton ���t�����h�錾���Ă�������
// @ Memo : protected �� private �ŃR���X�g���N�^�Apublic �Ńf�X�g���N�^��錾���Ă�������
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


    std::mutex m_mutex; // �T�u�N���X�p�~���[�e�b�N�X

private:
    static std::mutex ms_updaetrMutex;       // �~���[�e�b�N�X
    static std::unique_ptr<T> ms_instance;   // �V���O���g���T�u�N���X

    Singleton(const Singleton &) = delete;
    Singleton& operator=(const Singleton &) = delete;
    Singleton(Singleton &&) = delete;
    Singleton& operator=(Singleton &&) = delete;
};


template <class T>
std::unique_ptr<T> Singleton<T>::ms_instance;    // �V���O���g���T�u�N���X
template <class T>
std::mutex Singleton<T>::ms_updaetrMutex; // �~���[�e�b�N�X


template<class T>
T* const Singleton<T>::Get(void) {
    //----- �C���X�^���X�̐������f
    if (!(ms_instance)) {
        //----- ���b�N
        std::lock_guard<std::mutex> lock(ms_updaetrMutex);

        //----- �C���X�^���X�̐������f
        if (!(ms_instance)) {
            //----- �C���X�^���X�����݂��Ȃ����ߐ���
            ms_instance = std::unique_ptr<T>(new T());
        }
    }

    //----- �C���X�^���X�̕ԋp
    return ms_instance.get();
}


// �C���X�^���X�̖����I���
template<class T>
void Singleton<T>::DeleteInstance(void) {
    //----- ���b�N
    std::lock_guard<std::mutex> lock(ms_updaetrMutex);

    //----- �����I�J��
    ms_instance.reset();
}


#endif // !define ____GENERICSINGLETON_H____
