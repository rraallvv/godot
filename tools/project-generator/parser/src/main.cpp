/*************************************************************************/
/*  main.cpp                                                             */
/*************************************************************************/
/* Copyright (c) 2014 Rhody Lugo.                                        */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <set>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

typedef vector<string> myvector;
typedef set<string> myset;

myvector supportedCompilers = {
	"g++",
	"gcc",
	"clang",
	"clang++",
};

string buildDir = "../../";

myvector excludeFlags = {
	"-c",
	"-g3",
	"-Wall",
	"-arch",
	"-l",
	"-framework",
	"-isysroot",
};

myvector excludeGroupingTargets = {
	//"libfreetype_builtin",
	//"libdrivers",
	//"godot",
	//"libmodules",
	//"libmain",
	//"libtests",
	//"libcore",
	//"libservers",
	//"libscene",
	//"libtool",
};

myvector excludeGroupingFiles = {
	"core/io/config_file.cpp",
	"core/io/resource_format_binary.cpp",
	"core/io/resource_format_xml.cpp",
	"drivers/chibi/cp_player_data_notes.cpp",
	"drivers/mpc/mpc_bits_reader.c",
	"drivers/mpc/mpc_decoder.c",
	"drivers/mpc/mpc_demux.c",
	"drivers/mpc/streaminfo.c",
	"drivers/png/resource_saver_png.cpp",
	"drivers/speex/kiss_fftr.c",
	"drivers/speex/modes_wb.c",
	"drivers/speex/modes_wb.c",
	"drivers/speex/modes.c",
	"drivers/speex/nb_celp.c",
	"drivers/speex/sb_celp.c",
	"drivers/squish/colourblock.cpp",
	"drivers/squish/singlecolourfit.cpp",
	"drivers/theora/huffdec.c",
	"drivers/vorbis/floor1.c",
	"drivers/vorbis/info.c",
	"drivers/vorbis/res0.c",
	"drivers/vorbis/sharedbook.c",
	"drivers/vorbis/window.c",
	"drivers/webp/dec/alpha.c",
	"drivers/webp/dsp/enc_sse2.c",
	"drivers/webp/dsp/enc.c",
	"drivers/webp/enc/alpha.c",
	"drivers/webp/enc/analysis.c",
	"drivers/webp/enc/cost.c",
	"drivers/webp/enc/filter.c",
	"drivers/webp/enc/frame.c",
	"drivers/webp/enc/iterator.c",
	"drivers/webp/enc/layer.c",
	"drivers/webp/enc/picture.c",
	"drivers/webp/enc/quant.c",
	"drivers/webp/enc/syntax.c",
	"drivers/webp/enc/tree.c",
	"drivers/webp/enc/vp8l.c",
	"drivers/webp/enc/webpenc.c",
	"drivers/webp/mux/demux.c",
	"drivers/webp/mux/muxedit.c",
	"drivers/webp/mux/muxinternal.c",
	"drivers/webp/mux/muxread.c",
	"drivers/webp/utils/huffman_encode.c",
	"servers/physics_2d/collision_solver_2d_sat.cpp",
	"servers/physics/joints/hinge_joint_sw.cpp",
	"servers/physics/joints/slider_joint_sw.cpp",
	"tools/docdump/doc_dump.cpp",
	"tools/freetype/freetype/src/sfnt/sfnt.c",


	"drivers/builtin_openssl2/crypto/rsa/rsa_ameth.c",
	"drivers/builtin_openssl2/crypto/ec/ec2_oct.c",
	"drivers/builtin_openssl2/crypto/ec/ec2_smpl.c",
	"drivers/builtin_openssl2/crypto/ec/ec_asn1.c",
	"drivers/builtin_openssl2/crypto/ec/ec_check.c",
	"drivers/builtin_openssl2/crypto/ec/ec_curve.c",
	"drivers/builtin_openssl2/crypto/ec/ec_cvt.c",
	"drivers/builtin_openssl2/crypto/ec/ec_key.c",
	"drivers/builtin_openssl2/crypto/ec/ec_lib.c",
	"drivers/builtin_openssl2/crypto/ec/ec_mult.c",
	"drivers/builtin_openssl2/crypto/ec/ec_oct.c",
	"drivers/builtin_openssl2/crypto/ec/ec_print.c",
	"drivers/builtin_openssl2/crypto/ec/ecp_mont.c",
	"drivers/builtin_openssl2/crypto/ec/ecp_nist.c",
	"drivers/builtin_openssl2/crypto/ec/ecp_nistp256.c",
	"drivers/builtin_openssl2/crypto/ec/ecp_nistp521.c",
	"drivers/builtin_openssl2/crypto/ec/ecp_nistputil.c",
	"drivers/builtin_openssl2/crypto/ec/ecp_oct.c",
	"drivers/builtin_openssl2/crypto/ec/ecp_smpl.c",
	"drivers/builtin_openssl2/crypto/engine/tb_asnmth.c",
	"drivers/builtin_openssl2/crypto/engine/tb_dsa.c",
	"drivers/builtin_openssl2/crypto/engine/tb_ecdh.c",
	"drivers/builtin_openssl2/crypto/engine/tb_ecdsa.c",
	"drivers/builtin_openssl2/crypto/engine/tb_rand.c",
	"drivers/builtin_openssl2/crypto/engine/tb_rsa.c",
	"drivers/builtin_openssl2/crypto/engine/tb_store.c",
};

bool findGroupName(string prevLib, string lib, string &groupName, int &start) {
	int end,n,m;
	start=0;

	m=(int)prevLib.length();
	n=(int)lib.length();

	while (start<m && start<n) {
		if (prevLib[start]==lib[start])
			start++;
		else
			break;
	}

	end=0;
	while (end<m && end<m) {
		if (prevLib[m-end-1]==lib[n-end-1])
			end++;
		else
			break;
	}

	if (m>n) {
		end=m-end;
	} else
		end=n-end;

	string sub = lib.substr(start, end-start);

	bool isGroup = !sub.empty() && sub.find_first_not_of("0123456789") == std::string::npos;

	if (isGroup) {
		// Remove the subgroup indice if it's in the lib name
		groupName = prevLib.substr(0, start);
		if (prevLib.length()>lib.length()) {
			groupName = groupName + prevLib.substr(end, prevLib.length()-end);
		} else {
			groupName = groupName + lib.substr(end, lib.length()-end);
		}
	} else {
		groupName = "";
	}

	return isGroup;
}

string trim(string s, const string start, const string end, bool invert=false) {
	size_t startpos = invert ? s.find(start) : s.find_first_not_of(start);
	if( string::npos != startpos )
		s = invert ? s.substr( 0, startpos ) : s.substr( startpos );
	size_t endpos = invert ? s.rfind(end) : s.find_last_not_of(end);
	if( string::npos != endpos )
		s = invert ? s.substr( endpos+1 ) : s.substr( 0, endpos+1 );
	return s;
}

bool getline(const string &str, string &sub, const myvector delimiters, size_t &from) {

	sub = "";

	if (from == string::npos || from >= str.length())
		return false;

	string delim;

	size_t pos = string::npos;

	for (auto d = delimiters.begin(); d != delimiters.end(); ++d) {
		size_t p = str.find(*d, from);
		if (p < pos) {
			pos = p;
			delim = *d;
		}
	}

	if (pos != string::npos) {
		for (size_t i=1; i<delim.length(); ++i) {
			if (delim.substr(i, delim.length()-i).compare(str.substr(from,delim.length()-i))==0) {
				from = from + delim.length()-i;
				break;
			}
		}
		sub = str.substr(from, pos-from);
		from = pos + delim.length();
	} else {
		sub = str.substr(from);
		from = string::npos;
	}

	sub = trim(sub, " \t", " \t");

	return true;
}

void findExeComponents(unordered_map<string,myvector> &objects,
					   myvector &list,
					   unordered_map<string,myset> &files,
					   unordered_map<string,string> &rawflags,
					   unordered_map<string,myset> &sources,
					   unordered_map<string,myset> &flags,
					   unordered_map<string,myset> &includes,
					   unordered_map<string,myset> &linkLibs) {

	for ( auto lit = list.begin(); lit != list.end(); ++lit ) {

		//cout << *lit << endl;
		myset l;
		myset link;
		myset fs;
		myset is;

		string s;
		size_t pos = 0U;

		while (getline(rawflags[*lit], s, {" -", ","}, pos)) {
			if (s.length()) {
				if (s.find("/")==string::npos) {
					fs.insert(s);
				} else {
					string si;
					size_t posi =0U;
					string prev;
					while (getline(s, si, {" "}, posi)) {
						if (si.length()) {
							if (si.find("/")==string::npos) {
								if (prev.find("framework")!=string::npos) {
									fs.insert("framework " + si);
								} else if (prev.find("isysroot")!=string::npos) {
									fs.insert("isysroot " + si);
								} else if (si.find("framework")==string::npos && si.find("isysroot")==string::npos) {
									fs.insert(si);
								}
							} else {
								//		cout << si << endl;
								//si = trim(si, ".", "/", true);
								for (auto it = files[si].begin(); it != files[si].end(); ++it) {
									//cout << si << " " << *it << endl;
									l.insert(*it);
								}
							}
						}
						prev = si;
					}
				}
			}
		}

		//		cout << objects[*lit].size() << endl;
		for (auto it = objects[*lit].begin(); it != objects[*lit].end(); ++it) {
			//			cout << *it << endl;
			if ((*it).find("lib")==string::npos) {
				//		cout << *it << " " << includes[*it].size() << endl;
				is.insert(includes[*it].begin(), includes[*it].end());
			} else {
				//		cout << *it << " " << includes[*it].size() << endl;
				link.insert(*it);
			}
		}

		//cout << includes["os_osx"].size() << endl;
		sources[*lit]=l;
		flags[*lit]=fs;
		includes[*lit]=is;
		linkLibs[*lit]=link;
	}
}

void findLibComponents(unordered_map<string,myvector> &objects,
					   myvector &list,
					   unordered_map<string,myset> &files,
					   unordered_map<string,string> &rawflags,
					   unordered_map<string,myset> &sources,
					   unordered_map<string,myset> &flags,
					   unordered_map<string,myset> &includes) {

	for ( auto lit = list.begin(); lit != list.end(); ++lit ) {

		myvector objs = objects[*lit];
		//cout << *lit << endl;
		myset l;
		myset fs;
		myset is;
		for ( auto it = objs.begin(); it != objs.end(); ++it ) {
			//cout << *it << endl;
			for ( auto eit = files[*it].begin(); eit != files[*it].end(); ++eit )
				l.insert(*eit);
			string f = rawflags[*it];

			string s;
			size_t pos = 0U;
			while (getline(f, s, {" -", ","}, pos)) {
				if (s.length()) {
					if (s[0]=='I') {
						//cout << "<<<" << s << endl;
						is.insert(s.substr(1, s.length()-1));
					}
					else
						fs.insert(s);
				}
			}

		}
		sources[*lit]=l;
		flags[*lit]=fs;
		includes[*lit]=is;
	}
}

void strReplace( string &s, const string &search, const string &replace )
{
	for( size_t pos = 0; ; pos += replace.length() )
	{
		 pos = s.find( search, pos );
			if( pos == string::npos ) break;

		 s.erase( pos, search.length() );
		 s.insert( pos, replace );
	}
}

void addSources(myset &sources, const string libName, const string inputDir, const string buildDir,ofstream &out, bool groupFiles = false) {

	const myvector groupingTypes = {".cpp", ".c"};

	int groupCount = 1;

	// Files in groupingTypes

	for (auto type = groupingTypes.begin(); type != groupingTypes.end(); ++type) {

		int filesCount = 0;
		const int maxGroupedFiles = 40;

		ofstream groupOutputFile;
		string groupFilename;
		groupFiles = groupFiles && sources.size();

		for ( auto it = sources.begin(); it != sources.end(); ++it) {

			size_t pos = (*it).find(*type);

			if (pos==string::npos || pos!=(*it).length()-(*type).length())
				continue;

			if (groupFiles && find(excludeGroupingFiles.begin(), excludeGroupingFiles.end(), *it) == excludeGroupingFiles.end()) {

				if (filesCount % maxGroupedFiles == 0) {

					if (groupOutputFile.is_open()) {
						groupOutputFile.close();
						out << "\t<source filename=\"" << groupFilename << "\" />" << endl;
					}

					groupFilename = trim(libName, ".", "/", true) + to_string(groupCount) + *type;
					groupFilename = buildDir + groupFilename;
					//		cout << groupFilename << endl;
					groupOutputFile.open(inputDir + groupFilename);

					groupCount++;
				}

				groupOutputFile << "#include \"" << *it << "\"" << endl;
				filesCount++;

			} else {
				out << "\t<source filename=\"" << buildDir << *it << "\" />" << endl;
			}
			//		cout << *it << endl;
		}

		if (groupFiles) {

			if (groupOutputFile.is_open()) {
				groupOutputFile.close();
				out << "\t<source filename=\"" << groupFilename << "\" />" << endl;
			}
		}
	}


	// File types not in groupingTypes

	for ( auto it = sources.begin(); it != sources.end(); ++it) {

		bool addFile = true;

		for (auto type = groupingTypes.begin(); type != groupingTypes.end(); ++type) {

			size_t pos = (*it).find(*type);

			if (pos!=string::npos && (pos==(*it).length()-(*type).length())) {
				addFile = false;
				break;
			}
		}

		if (addFile) {
			out << "\t<source filename=\"" << buildDir << *it << "\" />" << endl;
			//		cout << *it << endl;
		}
	}
}

int main(int argc, char** argv) {

	string inputFile;
	string platform;
	bool groupFiles = false;
	string dataFiles;
	string resourceFiles;

	// Parse command-line arguments

	for (int i=1; i<argc; ++i) {

		string arg = argv[i];

		if (arg.find("i=")==0)
			inputFile = arg.substr(2, arg.length()-2);

		else if (arg.find("p=")==0)
			platform = arg.substr(2, arg.length()-2);

		else if (arg.find("g=yes")==0)
			groupFiles = true;

		else if (arg.find("d=")==0)
			dataFiles = arg.substr(2, arg.length()-2);

		else if (arg.find("r=")==0)
			resourceFiles = arg.substr(2, arg.length()-2);
	}

	if (!inputFile.length() || !platform.length()) {
		cout << argv[0] << " i=ouput.txt p=[mac_os_x|ios]" << endl;
		return errno;
	}

	ifstream t;
	t.open(inputFile, ifstream::in);
	if (!t.is_open()) {
		cout << "Couldn't open output file '" << inputFile << "'" << endl;
		return errno;
	}

	if (platform.compare("mac_os_x")!=0 && platform.compare("ios")!=0) {
		cout << "Platform '" << platform << "' not supported" << endl;
		return errno;
	}

	size_t pos = inputFile.find_last_of("/\\");
	string inputDir = inputFile.substr(0,pos+1);


	// Begin parsing input file

	cout << "parsing: '" << inputFile << "'" << endl;

	stringstream buffer;
	buffer << t.rdbuf();
	string str = buffer.str();

	stringstream stream(str);
	string line;

	myvector excs;
	myvector libs;
	unordered_map<string,string> rawflags;
	unordered_map<string,myset> files;
	unordered_map<string,myvector> objects;
	unordered_map<string,myset> sources;
	unordered_map<string,myset> flags;
	unordered_map<string,myset> includes;
	unordered_map<string,myset> linkLibs;
	myvector objFiles;
	string prevLib;

	while (getline(stream, line)) {

		bool supported = false;

		for (auto it = supportedCompilers.begin(); it != supportedCompilers.end(); ++it) {
			if (line.find(*it + " -o")!=string::npos)
				supported = true;
		}

		if (supported) {

			size_t s = line.find(" -o ");
			size_t e = line.find(" ", s+4);
			string obj = line.substr(s+4, e-s-4);
			//		cout << obj << endl;
			//obj=trim(obj, ".", "/", true);
			string value = line.substr(e+1, line.length()-e-1);
			myset l;

			if (line.find(" -c ")==string::npos) {
				// Object is executable
				excs.push_back(obj);
				//		l.insert("");
				//		files[obj]=l;
				//		cout << ">>" << obj << endl;

				rawflags[obj]=value;


				string s;
				myvector objs;
				size_t pos = 0U;
				while (getline(value, s, {" -", ","}, pos)) {
					if (s.length() && s.find("/")!=string::npos) {

						string si;
						size_t posi = 0U;
						string prevObj;

						while (getline(s, si, {" "}, posi)) {
							if (si.length() && si.find("/")!=string::npos) {
								//		cout << si << endl;
								//si = trim(si, ".", "/", true);

								int start;
								string groupName;
								bool isGroup = findGroupName(prevObj, si, groupName, start);

								if (isGroup) {
									// Remove the subgroup indice if it's in the lib name
									//		cout << prevObj << " " << groupName << endl;
									std::replace(objs.begin(), objs.end(), prevObj, groupName);

								} else {
									//		cout << ">>" << objFile << " " << objs.size() << endl;
									objs.push_back(si);
								}
								prevObj = si;
							}
						}
					}
				}
				//		cout << obj << " " << objs.size();
				objects[obj]=objs;

			} else {
				// Object is part of library or executable
				size_t pos = value.rfind(" ");
				string src = value.substr(pos+1, value.length()-pos-1);
				l.insert(src);
				files[obj]=l;
				rawflags[obj]=value = value.substr(0, pos);
				//cout << value << endl;

				string s;
				myvector objs;
				size_t posl = 0U;

				while (getline(value, s, {" -", ","}, posl)) {
					if (s.length() && s.find("/")!=string::npos) {
						string si;
						size_t posi = 0U;
						string prevObj;

						while (getline(s, si, {" "}, posi)) {
							if (si.length() && si.find("/")!=string::npos) {
								if (si[0]=='I')
									includes[obj].insert(s.substr(1, s.length()-1));
							}
						}
					}
				}
				//		cout << obj << " " << objs.size() << endl;
				objects[obj]=objs;
			}

		} else if (line.find("ar rc ")!=string::npos) {
			// Object is library

			size_t s = line.find("ar rc ");
			size_t e = line.find(" ", s+6);
			string lib = line.substr(s+6, e-s-6);
			//lib=trim(lib, ".", "/", true);


			// Add the objects linked with this particular object
			string list = line.substr(e+1, line.length()-e-1);
			stringstream ss(list);
			string objFile;

			objFiles.clear();

			while (getline(ss, objFile, ' ')) {
				//objFile=trim(objFile, ".", "/", true);
				objFiles.push_back(objFile);
			}


			// Chech whether the object's name is withing a group
			int start;
			string groupName;
			bool isGroup = findGroupName(prevLib, lib, groupName, start);


			if (isGroup) {
				// Add this to the previous group if they are grouped
				if (prevLib.compare(groupName)!=0) {
					// Remove the subgroup indice if it's in the lib name
					objects[groupName] = objects[prevLib];
					objects.erase(prevLib);
					std::replace(libs.begin(), libs.end(), prevLib, groupName);
					prevLib = groupName;
				}
				for (int i=0; i<objFiles.size(); ++i)
					objects[groupName].push_back(objFiles[i]);
			} else {
				// Start a new group
				objects[lib]=objFiles;
				prevLib = lib;
				libs.push_back(lib);
			}
		}
	}

	findLibComponents(objects, libs, files, rawflags, sources, flags, includes);

	findExeComponents(objects, excs, files, rawflags, sources, flags, includes, linkLibs);


#if 0
	cout << "******** objects:" << endl;
	for ( auto lit = linkLibs.begin(); lit != linkLibs.end(); ++lit ) {
		cout << lit->first << endl;
		myset objs = includes[lit->first];
		for ( auto it = objs.begin(); it != objs.end(); ++it ) {
			cout << *it << endl;
		}
	}

	return 0;
#endif


	// executable targets
	for ( auto tit = excs.begin(); tit != excs.end(); ++tit ) {

		string filename = trim(*tit, ".", "/", true)+".xml";
		string outputFile = inputDir+filename;

		cout << "generating: '" + outputFile << "'" << endl;
		ofstream out(outputFile);

		out << "<target name=\"" << *tit << "\" type=\"executable\">" << endl;

		// dependencies
		for ( auto it = linkLibs[*tit].begin(); it != linkLibs[*tit].end(); ++it) {

			out << "\t<dependency filename=\"" << trim(*it, ".", "/", true) << ".xml\" merge=\"true\" />" << endl;
		}

		out << endl;

		// include paths
		for ( auto it = includes[*tit].begin(); it != includes[*tit].end(); ++it) {

			string path;
			struct stat info;
			if ((*it).find_first_of("/\\")==0) {
				path = *it;
				if (!stat( path.c_str(), &info )) {
					out << "\t<header directory=\"" << path << "\" />" << endl;
					//cout << path << endl;
				}
			} else {
				path = buildDir + *it;
				if (!stat( (inputDir + path).c_str(), &info )) {
					out << "\t<header directory=\"" << path << "\" />" << endl;
					//cout << path << endl;
				}
			}
		}

		out << endl;

		// compiler flags
		out << "\t<compiler program=\"clang\" flags=\"";
		//myset compilerFlags = flags[*tit];
		//for ( auto it = compilerFlags.begin(); it != compilerFlags.end(); ++it) {
		for ( auto it = flags[*tit].begin(); it != flags[*tit].end(); ++it) {

			string flag = "-" + *it;
			bool exclude = false;
			for (auto eflag = excludeFlags.begin(); eflag != excludeFlags.end(); ++eflag) {

				if (flag.find(*eflag)==0)
					exclude = true;
			}
			if (!exclude) {
				strReplace(flag, "\"", "");
				out << flag << " ";
			}
		}
		out << "\" />" << endl;

		out << endl;


		// linker flags
		out << "\t<!--<linker program=\"clang\" flags=\"";
		for ( auto it = linkLibs[*tit].begin(); it != linkLibs[*tit].end(); ++it) {

			if ((*it).find("lib")==0) {
				out << "-l" << (*it).substr(3, (*it).length()-3) << " ";
			}
		}
		out << "\" />-->" << endl;

		out << endl;

		// sources

		bool group = true;
		for (auto libName = excludeGroupingTargets.begin(); libName != excludeGroupingTargets.end(); ++libName) {

			if ((*tit).find(*libName)!=string::npos)
				group = false;
		}

		addSources(sources[*tit], *tit, inputDir, buildDir, out, groupFiles && group);

		out << endl;

		out << "\t<configuration name=\"debug\"></configuration>" << endl;
		out << "\t<configuration name=\"release\"></configuration>" << endl;
		out << "\t<configuration name=\"adhoc\"></configuration>" << endl;
		out << "\t<configuration name=\"distribution\"></configuration>" << endl;

		out << endl;

		out << "\t<platform name=\"" << platform << "\">" << endl;

		for (auto it = flags[*tit].begin(); it != flags[*tit].end(); ++it) {
			if ((*it).find("framework")==0) {
				string framework = (*it).substr(10, (*it).length()-10) + ".framework";
				out << "\t\t<library filename=\"" << framework << "\" />" << endl;
				//cout << framework << endl;
			} else if ((*it)[0]=='l') {
				string library = "lib" + (*it).substr(1, (*it).length()-1) + ".dylib";
				out << "\t\t<library filename=\"" << library << "\" />" << endl;
			}
		}
		out << "\t</platform>" << endl;

		out << endl;

		out << "</target>" << endl;

		out.close();


		// library targets
		for ( auto lit = linkLibs[*tit].begin(); lit != linkLibs[*tit].end(); ++lit ) {

			string filename = trim(*lit, ".", "/", true)+".xml";
			string outputFile = inputDir+filename;

			cout << "generating: '" + outputFile << "'" << endl;
			ofstream out(outputFile);

			out << "<target name=\"" << *lit << "\" type=\"library\">" << endl;

			// include paths
			for ( auto it = includes[*lit].begin(); it != includes[*lit].end(); ++it) {

				string path;
				struct stat info;
				if ((*it).find_first_of("/\\")==0) {
					path = *it;
					if (!stat( path.c_str(), &info )) {
						out << "\t<header directory=\"" << path << "\" />" << endl;
						//cout << path << endl;
					}
				} else {
					path = buildDir + *it;
					if (!stat( (inputDir + path).c_str(), &info )) {
						out << "\t<header directory=\"" << path << "\" />" << endl;
						//cout << path << endl;
					}
				}
			}

			out << endl;

			// compiler flags
			out << "\t<compiler program=\"clang\" flags=\"";
			for ( auto it = flags[*lit].begin(); it != flags[*lit].end(); ++it) {

				string flag = "-" + *it;
				bool exclude = false;
				for (auto eflag = excludeFlags.begin(); eflag != excludeFlags.end(); ++eflag) {

					if (flag.find(*eflag)==0)
						exclude = true;
				}
				if (!exclude) {
					strReplace(flag, "\"", "");
					out << flag << " ";
				}
			}
			out << "\" />" << endl;

			out << endl;

			// linker flags
			out << "\t<!--<linker program=\"clang\" flags=\"";
			for ( auto it = linkLibs[*lit].begin(); it != linkLibs[*lit].end(); ++it) {

				if ((*it).find("lib")==0) {
					out << "-l" << (*it).substr(3, (*it).length()-3) << " ";
				}
			}
			out << "\" />-->" << endl;

			out << endl;

			// sources

			bool group = true;
			for (auto libName = excludeGroupingTargets.begin(); libName != excludeGroupingTargets.end(); ++libName) {

				if ((*lit).find(*libName)!=string::npos)
					group = false;
			}

			addSources(sources[*lit], *lit, inputDir, buildDir, out, groupFiles && group);

			out << endl;

			out << "\t<configuration name=\"debug\"></configuration>" << endl;
			out << "\t<configuration name=\"release\"></configuration>" << endl;
			out << "\t<configuration name=\"adhoc\"></configuration>" << endl;
			out << "\t<configuration name=\"distribution\"></configuration>" << endl;
			
			out << endl;
			
			out << "</target>" << endl;
			
			out.close();
		}
	}

	if (!excs.size()) {
		cout << "No executable files." << endl;
		return errno;
	}

	string targetName = trim(excs[0], ".", "/", true);

	cout << "running project generator script for '" << targetName << ".xml'" << endl;

	string cmd = "cd "+ inputDir + " && " + "source/generate.py -i " + targetName + ".xml -p " + platform + " -g xcode -n " + targetName;

	if (!dataFiles.empty())
		cmd += " -d " + dataFiles;

	if (!resourceFiles.empty())
		cmd += " -r " + resourceFiles;

	cout << cmd << endl;

	system(cmd.c_str());

	cout << "finished" << endl;

	return 0;
}
