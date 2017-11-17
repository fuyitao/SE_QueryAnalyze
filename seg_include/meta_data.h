#pragma once
/*
* Manager meta data
* 1. brand info
* 2. category mapping
* 3. product category mapping
*/

#include <map>
#include <vector>
#include <string>

namespace nlp {

class MetaDataManager {
  public:
    MetaDataManager();
    virtual ~MetaDataManager();

    bool Init(std::string meta_dir, std::string ccode_dir);

    inline bool GetProductCat(std::string product,
                              std::string* cat) {
      std::map<std::string, std::string>::iterator iter = 
                                   product_cat_map_.find(product);
      if (iter == product_cat_map_.end()) {
        *cat = "";
        return false;
      }
      *cat = iter->second;
      return true;
    }

    inline bool MapCat(int cat_in, int* cat_out) {
      if (Map360Cat(cat_in, cat_out)) {
        return true;
      }
      if (MapOldCat(cat_in, cat_out)) {
        return true;
      }
      return false;
    }

    inline bool Map360Cat(int cat_in, int* cat_out) {
      std::map<int, int>::iterator iter = cat360_map_.find(cat_in);
      if (iter == cat360_map_.end()) {
        *cat_out = 0;
        return false;
      }
      *cat_out = iter->second;
      return true;
    }

    inline bool MapOldCat(int cat_in, int* cat_out) {
      std::map<int, int>::iterator iter = catold_map_.find(cat_in);
      if (iter == catold_map_.end()) {
        *cat_out = 0;
        return false;
      }
      *cat_out = iter->second;
      return true;
 
    }

    inline bool GetCatId(std::string cat, int* cat_id) {
      std::map<std::string, int>::iterator iter = cat_id_map_.find(cat);
      if (iter == cat_id_map_.end()) {
        *cat_id = 0;
        return false;
      }
      *cat_id = iter->second;
      return true;
    }

    inline bool GetCatName(int cat_id, std::string* cat_name) {
      std::map<int, std::string>::iterator iter = cat_name_map_.find(cat_id);
      if (iter == cat_name_map_.end()) {
        *cat_name = "";
        return false;
      }
      *cat_name = iter->second;
      return true;
    }

    inline std::vector<int>* GetSubCatFromBrand(std::string brand) {
      BrandIterType iter = brand_cat_map_.find(brand);
      if (iter == brand_cat_map_.end()) {
        return NULL;
      }
      return &(iter->second);
    }

    inline std::vector<int>* GetSubCatFromProduct(std::string product) {
      BrandIterType iter = product_subcat_map_.find(product);
      if (iter == product_subcat_map_.end()) {
        return NULL;
      }
      return &(iter->second);
    }

  private:

    std::map<std::string, std::string> product_cat_map_;

    std::map<int, int> cat360_map_;
    std::map<int, int> catold_map_;
    std::map<int, std::string> cat_name_map_;
    std::map<std::string, int> cat_id_map_;

    std::map<std::string, std::vector<int> > brand_cat_map_;
    typedef std::map<std::string, std::vector<int> >::iterator BrandIterType;
    std::map<std::string, std::vector<int> > product_subcat_map_;

    void AddToBrandMap(std::string brand, int cat);
    void AddToProductMap(std::string product, int cat);
}; // end of class

} // end of namespace

