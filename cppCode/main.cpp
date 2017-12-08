#include "iostream"
//#include "src/PreProcess.h"
#include "boost/program_options.hpp"
#include <gtest/gtest.h>
#include "string"
#include "src/PreProcess.h"

#include <iterator>
#define GENOMEFA "../datasets/genome.fa"
using namespace boost::program_options;
using namespace std;
namespace po = boost::program_options;

void printHelp(){
    printf("Run the program as follows: ./cppCode <mode> <arg>\nPossible Modes: \n 0: Runs all Tests\n1:preprocess inputfilename outputfilename\n2:construct_debruijn_graph\n");
}

int main(int argc, char *argv[]) {
    try {

        int limit;
        po::options_description desc("Allowed options");
        desc.add_options()
                ("help", "produce help message")
                ("choice", po::value<int>(), "select the methods to run: \n"
                        "0: Run the test cases\n"
                        "1: preprocess the input file to the output file. Please give the container paths here. (if using docker).")
                ("input-file", po::value<string>(), "input file, should be a fastq")
                ("output-file", po::value<string>(), "output file, can be any file ")
                ("limit", po::value<int>(&limit)->default_value(1000) , "limit to number of sequence reads while preprocessing (Choice 1). Defaults to 1000 sequence reqds from fastq files");

                ;

        po::variables_map vm;
        po::store(po::parse_command_line(argc, (const char *const *) argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            cout << desc << "\n";
            return 0;
        }

        if (vm.count("choice")) {
            cout << "choice is selected to "
                 << vm["choice"].as<int>() << ".\n";
            int c = vm["choice"].as<int>();
            switch (c){
                case 0:
                    testing::InitGoogleTest(&argc, argv);
                    return RUN_ALL_TESTS();
                case 1:
                    if(!vm.count("input-file") || !vm.count("output-file")){
                        printf("input-file and output-file are mandatory params for preprocess\n");
                        break;
                    }else{
//                        string result = "/Users/nagasaty/0classes/bdb/DeBruijnGraph/datasets/outputs/reduced.fq";
                        PreProcess *obj = new PreProcess(vm["input-file"].as<string>(), vm["output-file"].as<string>());
                        obj->truncate(limit);
                        printf("Preprocessed the file from %s to  %s...\n", vm["input-file"].as<string>().c_str(), vm["output-file"].as<string>().c_str());
                    }
            }
        } else{
            cout << "Invalid Choice selected. Please select the choice from 0 - 1, \n" << desc << endl;
        }
    }
    catch(exception& e) {
        cerr << "error: " << e.what() << "\n";
        return 1;
    }
    catch(...) {
        cerr << "Exception of unknown type!\n";
    }

    return 0;

////    printf("Program Name Is: %s",argv[0]);
//    if(argc==1)
//        printf("\nNo Extra Command Line Argument Passed Other Than Program Name");
//    if(argc>=2)
//    {
//        int option =  static_cast<int>( *argv[1]);
//        switch(option){
//            case 0:
//                testing::InitGoogleTest(&argc, argv);
//                RUN_ALL_TESTS();
//                break;
//            case 1:
//                if(argc<=4){
//                    printf("Need atleast 2 parameters, input file , output file\n");
//                }
//                PreProcess obj = PreProcess(string(*argv[2]), string(*argv[3]));
//                printf("Processing file with limit");
//
//        }
//        printf("\nNumber Of Arguments Passed: %d",argc);
//        printf("\n----Following Are The Command Line Arguments Passed----");
//        for(int counter=0;counter<argc;counter++)
//            printf("\nargv[%d]: %s",counter,argv[counter]);
//    }
//    return 0;
}

