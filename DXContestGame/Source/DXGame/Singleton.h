#ifndef ____GENERICSINGLETON_H____
#define ____GENERICSINGLETON_H____

#include <memory>


// シングルトン用抽象クラス
// @ Memo : ACSingleton をフレンド宣言してください
// @ Memo : protected や private でコンストラクタを宣言してください
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


private:
    static std::unique_ptr<T> ms_singleton; // シングルトンサブクラス

    Singleton(const Singleton &) = delete;
    Singleton& operator=(const Singleton &) = delete;
    Singleton(Singleton &&) = delete;
    Singleton& operator=(Singleton &&) = delete;
};


template <class T>
std::unique_ptr<T> Singleton<T>::ms_singleton;    // シングルトンサブクラス


template<class T>
T* const Singleton<T>::Get(void) {
    //----- インスタンスの生成判断
    if (!(ms_singleton)) {
        //----- インスタンスが存在しないため生成
        ms_singleton = std::unique_ptr<T>(new T());
    }

    //----- インスタンスの返却
    return ms_singleton.get();
}


// インスタンスの明示的解放
template<class T>
void Singleton<T>::DeleteInstance(void) {
    //----- 明示的開放
    ms_singleton.reset();
}


#endif // !define ____GENERICSINGLETON_H____
