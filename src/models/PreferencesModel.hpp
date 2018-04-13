#ifndef PreferencesModel_hpp
#define PreferencesModel_hpp

#include "AbstractSqliteModel.hpp"

class PreferencesModel : public AbstractSqliteModel {
private:
    void initialize();



public:
    PreferencesModel();
    ~PreferencesModel();
};

#endif /* PreferencesModel_hpp */
