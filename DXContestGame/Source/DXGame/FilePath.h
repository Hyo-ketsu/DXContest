#ifndef ____FILEPATH_H____
#define ____FILEPATH_H____


namespace FilePath {
    const std::string ASSETS_PATH = "Assets/";
#ifdef _DEVELOP
    const std::string SOLUTION_FILE_PATH = "";
#endif // _DEVELOP
#ifdef _GAME
    const std::string SOLUTION_FILE_PATH = "../";
#endif // _GAME
    const std::string TEXTURE_PATH = SOLUTION_FILE_PATH + FilePath::ASSETS_PATH.c_str() + std::string("Texture/");
    const std::string MODEL_PATH   = SOLUTION_FILE_PATH + FilePath::ASSETS_PATH.c_str() + std::string("Model/");
    const std::string SHADER_PATH  = SOLUTION_FILE_PATH + FilePath::ASSETS_PATH.c_str() + std::string("Shader/");
}


#endif // !____FILEPATH_H____
