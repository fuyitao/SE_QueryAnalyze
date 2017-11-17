#pragma once
/*
* 1. category mapping
*/

#include <map>
#include <vector>
#include <string>
namespace nlp {

    class CategoryMapping {
        public:
            CategoryMapping();
            virtual ~CategoryMapping();
            bool Init(std::string dict_dir);
            int get(std::string new_category, char *current_strategy);     
        private:
            std::map<std::string, std::string> new_to_old_map_;
            typedef std::map<std::string, std::string >::iterator CategoryMappingIter;
    };
} // end of namespace

