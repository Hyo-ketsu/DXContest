#include <DXGame/ScoreIO.h>
#include <fstream>


// スコアファイルを読み込み
const ScoreArray ScoreIO::ReadScore(void) {
    //----- 変数宣言
    std::vector<unsigned int> score;  // 返却用スコア動的配列
    ScoreArray ret; // 返却用スコア配列
    std::string line;   // 読み込んだ行
    std::string token;  // 読み込んだ文字列

    //----- 空か判定
    FilePathEmpty();

    //----- 読み込みストリーム宣言
    std::ifstream file(m_filePath);
    if (!(file)) {
        ret.fill(0);
        return ret;
    }

    //----- 数値読み込み
    while (std::getline(file, line)) {
        //----- 読み込んだ行の解析
        for (auto lineChar : line) {
            //----- 区切り文字（,）若しくは改行に到達したか
            if (lineChar == ',' || lineChar == '\n') {
                //----- 到達。読み込んだトークンを変換
                if (token.empty() == false) {
                    //----- トークンが空でない。数値変換
                    score.push_back(std::stoi(token));

                    //----- トークン初期化
                    token.clear();
                }
            }
            else {
                //----- 到達していない。1文字ずつトークンに追加
                token += lineChar;
            }
        }
    }

    //----- 動的配列から返却配列へ移す
    ret.fill(0);    // その順位に数値がなければ 0 にするため
    for (int i = 0;; i++) {
        //----- 動的配列、返却配列どちらも範囲内か（ガード節）
        if (score.size() >= i) break;
        if (ret.size()   >= i) break;

        //----- 値の受け渡し
        ret[i] = score[i];
    }

    //----- 返却
    return std::move(ret);
}
// スコアファイルを書き込み
void ScoreIO::WriteScore(const ScoreArray& scoreData) {
    //----- 空か判定
    FilePathEmpty();

    // ファイルオープン
    std::ofstream file(m_filePath);

    //----- 書き込み
    for (auto it : scoreData) {
        //----- スコア出力
        file << it << ',';

        //----- 改行
        file << std::endl;
    }
}


// 読み込みファイルパスが空か判定、例外を吐く
void ScoreIO::FilePathEmpty(void) const {
    //----- 判定
    if (m_filePath.empty()) {
        //----- 文字列が空。例外を吐く
        throw std::exception("Error! ScoreIO file path empty");
    }
}
