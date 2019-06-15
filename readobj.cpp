int split(std::string str, std::string pattern, std::vector<std::string> &words)
{
       std::string::size_type pos;
       std::string word;
       int num = 0;
       str += pattern;
       std::string::size_type size = str.size();
       for (auto i = 0; i < size; i++) {
              pos = str.find(pattern, i);
              if (pos == i) {
                     continue;//if first string is pattern
              }
              if (pos < size) {
                     word = str.substr(i, pos - i);
                     words.push_back(word);
                     i = pos + pattern.size() - 1;
                     num++;
              }
       }
       return num;
}

void loadObjFile(std::string filename, std::vector<cv::Point3f> &v_array, std::vector<cv::Point2f> &vt_array,
       std::vector<cv::Point3f> &vn_array, std::vector<std::vector<FACE>> &f_array)
{      
       std::ifstream fin(filename);
       std::string str;
       std::vector<std::string> words;
       cv::Point3f v;
       cv::Point2f vt;
       cv::Point3f vn;
       std::vector<FACE> face(3);
       int num = 0;
       while (!fin.eof()) {
              std::getline(fin, str);
              words.clear();
              num = split(str, " ", words);
              //std::cout << "num = " << num << std::endl;
              //getchar();
              if (num == 4 && words[0] == "v") {
                     v.x = atof(words[1].c_str());
                     v.y = atof(words[2].c_str());
                     v.z = atof(words[3].c_str());
                     v_array.push_back(v);
              }
              else if (num == 4 && words[0] == "vt") {
                     vt.x = atof(words[1].c_str());
                     vt.y = atof(words[2].c_str());
                     vt_array.push_back(vt);
              }
              else if (num == 4 && words[0] == "vn") {
                     vn.x = atof(words[1].c_str());
                     vn.y = atof(words[2].c_str());
                     vn.z = atof(words[3].c_str());
                     vn_array.push_back(vn);
              }
              else if (num == 4 && words[0] == "f") {
                     for (int i = 1; i < words.size(); ++i) {
                           std::vector<std::string> str_tmp;
                           split(words[i], "/", str_tmp);
                           face[i - 1].v_index = atoi(str_tmp[0].c_str()) - 1;//modify start from 0
                           face[i - 1].vt_index = atoi(str_tmp[1].c_str()) - 1;
                           if (str_tmp.size() >= 3) {
                                  face[i - 1].vn_index = atoi(str_tmp[2].c_str()) - 1;
                           }
                           
                     }
                     f_array.push_back(face);
              }
       }
}