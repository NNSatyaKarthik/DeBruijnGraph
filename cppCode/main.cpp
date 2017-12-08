#include "iostream"
//#include "src/PreProcess.h"
#include "boost/filesystem.hpp"
#include <gtest/gtest.h>
#include "string"
#define GENOMEFA "../datasets/genome.fa"
using namespace boost::filesystem;
using namespace std;


void printHelp(){
    printf("Run the program as follows: ./cppCode <mode> <arg>\nPossible Modes: \n 0: Runs all Tests\n1:preprocess inputfilename outputfilename\n2:construct_debruijn_graph\n");
}

int main(int argc, char *argv[]) {
    const  path p("..");
//    printf(absolute(p, current_path()));
    cout << canonical(p) << endl;
//    testing::InitGoogleTest(&argc, argv);
//    RUN_ALL_TESTS();
//    return 0;
//    printHelp();
//
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

