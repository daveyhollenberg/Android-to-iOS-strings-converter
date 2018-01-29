#include <iostream>
#include <fstream>
#include <string>

using namespace std;
// << android to ios string resource file converter >>
//  this program converts android strings.xml files to xcode (swift) Localizable.strings files
//  created by Davey Hollenberg (2018)

// << variables >>
int MAX_LENGTH = 50; // max number of characters in the name/text
bool REMOVE_BACKSLASH = true; // remove the backslash in the resource file
string INPUT_FILE_NAME = "strings.xml";// android strings.xml file name
string OUTPUT_FILE_NAME = "output.txt";// output Localizable.strings file name

// << start of program >>
int main(){
  ifstream file(INPUT_FILE_NAME);
  ofstream output(OUTPUT_FILE_NAME);
  string line;
  while(getline(file,line)){
    if(REMOVE_BACKSLASH){
      bool bs = true;
      while(bs){
        int i = line.find('\\');
        if (i!=std::string::npos){
          line.replace(i,1,"");
        }else{bs=false;}
      }
    }
    char text[MAX_LENGTH];
    char tag[MAX_LENGTH];
    int starttag = line.find('"');
    int endtag = line.rfind('"');
    if(starttag!=-1&&endtag!=-1){
      int length = line.copy(tag,endtag-starttag-1,starttag+1);
      tag[length] = '\0';
      int starttext = line.find('>');
      int endtext = line.rfind('<');
      if(starttext!=-1&&endtext!=-1){
        int length = line.copy(text,endtext-starttext-1,starttext+1);
        text[length] = '\0';
        output << '"' << tag << "\" = \"" << text << "\";" << endl;
      }
    }
  }
  file.close();
  output.close();
  return 0;
}
