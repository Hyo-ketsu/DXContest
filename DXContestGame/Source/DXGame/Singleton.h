#ifndef ____GENERICSINGLETON_H____
#define ____GENERICSINGLETON_H____

#include <mutex>
#include <memory>
#include <type_traits>


// シングルトン用抽象クラス
// @ Memo : ACSingleton をフレンド宣言してください
// @ Memo : protected や private でコンストラクタ、public でデストラクタを宣言してください
// @ Temp : 返却するこのクラスのサブクラス
template<class T>
class Singleton {
public:
    // インスタンスの取得
    // @ Ret  : 一個しかないことが明確なインスタンス
    static T* const Get(void);


    // インスタンスの明示的解放
    static void DeleteInstance(void);

protected:
    // コンストラクタ
    Singleton<T>(void) {}


    // デストラクタ
    virtual ~Singleton<T>(void) {}


    std::mutex m_mutex; // サブクラス用ミューテックス

private:
    static std::mutex ms_updaetrMutex;       // ミューテックス
    static std::unique_ptr<T> ms_instance;   // シングルトンサブクラス

    Singleton(const Singleton &) = delete;
    Singleton& operator=(const Singleton &) = delete;
    Singleton(Singleton &&) = delete;
    Singleton& operator=(Singleton &&) = delete;
};


template <class T>
std::unique_ptr<T> Singleton<T>::ms_instance;    // シングルトンサブクラス
template <class T>
std::mutex Singleton<T>::ms_updaetrMutex; // ミューテックス


template<class T>
T* const Singleton<T>::Get(void) {
    //----- インスタンスの生成判断
    if (!(ms_instance)) {
        //----- ロック
        std::lock_guard<std::mutex> lock(ms_updaetrMutex);

        //----- インスタンスの生成判断
        if (!(ms_instance)) {
            //----- インスタンスが存在しないため生成
            ms_instance = std::unique_ptr<T>(new T());
        }
    }

    //----- インスタンスの返却
    return ms_instance.get();
}


// インスタンスの明示的解放
template<class T>
void Singleton<T>::DeleteInstance(void) {
    //----- ロック
    std::lock_guard<std::mutex> lock(ms_updaetrMutex);

    //----- 明示的開放
    ms_instance.reset();
}


#endif // !define ____GENERICSINGLETON_H____
