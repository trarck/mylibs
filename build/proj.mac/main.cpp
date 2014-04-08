
#include <iostream>
#include <yh/yh.h>

#include "tests/io/test_buffer.h"
#include <yh/shell/OptionParser.h>

USING_NS_YH;

using namespace yh::cli;
using namespace yh::cli::detail;

int main(int argc, const char * argv[])
{
    
    yh::cli::OptionParser op("Usage: {progname} [options] [[script] scriptArgs*]");
    
    op.setDescription("The SpiderMonkey shell provides a command line interface to the "
                      "JavaScript engine. Code and file options provided via the command line are "
                      "run left to right. If provided, the optional script argument is run after "
                      "all options have been processed. Just-In-Time compilation modes may be enabled via "
                      "command line options.");
    op.setDescriptionWidth(72);
    op.setHelpWidth(80);
    op.setVersion("1.0");
    
    if (!op.addMultiStringOption('f', "file", "PATH", "File path to run")
        || !op.addMultiStringOption('e', "execute", "CODE", "Inline code to run")
        || !op.addBoolOption('i', "shell", "Enter prompt after running code")
        || !op.addBoolOption('m', "jm", "No-op (still used by fuzzers)")
        || !op.addBoolOption('\0', "no-jm", "No-op (still used by fuzzers)")
        || !op.addBoolOption('n', "ti", "Enable type inference (default)")
        || !op.addBoolOption('\0', "no-ti", "Disable type inference")
        || !op.addBoolOption('c', "compileonly", "Only compile, don't run (syntax checking mode)")
        || !op.addBoolOption('w', "warnings", "Emit warnings")
        || !op.addBoolOption('W', "nowarnings", "Don't emit warnings")
        || !op.addBoolOption('s', "strict", "Check strictness")
        || !op.addBoolOption('d', "debugjit", "Enable runtime debug mode for method JIT code")
        || !op.addBoolOption('a', "always-mjit", "No-op (still used by fuzzers)")
        || !op.addBoolOption('D', "dump-bytecode", "Dump bytecode with exec count for all scripts")
        || !op.addBoolOption('b', "print-timing", "Print sub-ms runtime for each file that's run")
        || !op.addStringOption('\0', "js-cache", "[path]",
                               "Enable the JS cache by specifying the path of the directory to use "
                               "to hold cache files")
        || !op.addBoolOption('\0', "js-cache-per-process",
                             "Generate a separate cache sub-directory for this process inside "
                             "the cache directory specified by --js-cache. This cache directory "
                             "will be removed when the js shell exits. This is useful for running "
                             "tests in parallel.")
#ifdef DEBUG
        || !op.addBoolOption('O', "print-alloc", "Print the number of allocations at exit")
#endif
        || !op.addOptionalStringArg("script", "A script to execute (after all options)")
        || !op.addOptionalMultiStringArg("scriptArgs",
                                         "String arguments to bind as |scriptArgs| in the "
                                         "shell's global")
#ifdef JS_THREADSAFE
        || !op.addIntOption('\0', "thread-count", "COUNT", "Use COUNT auxiliary threads "
                            "(default: # of cores - 1)", -1)
#endif
        || !op.addBoolOption('\0', "ion", "Enable IonMonkey (default)")
        || !op.addBoolOption('\0', "no-ion", "Disable IonMonkey")
        || !op.addBoolOption('\0', "no-asmjs", "Disable asm.js compilation")
        || !op.addStringOption('\0', "ion-gvn", "[mode]",
                               "Specify Ion global value numbering:\n"
                               "  off: disable GVN\n"
                               "  pessimistic: use pessimistic GVN\n"
                               "  optimistic: (default) use optimistic GVN")
        || !op.addStringOption('\0', "ion-licm", "on/off",
                               "Loop invariant code motion (default: on, off to disable)")
        || !op.addStringOption('\0', "ion-edgecase-analysis", "on/off",
                               "Find edge cases where Ion can avoid bailouts (default: on, off to disable)")
        || !op.addStringOption('\0', "ion-range-analysis", "on/off",
                               "Range analysis (default: on, off to disable)")
        || !op.addBoolOption('\0', "ion-check-range-analysis",
                             "Range analysis checking")
        || !op.addStringOption('\0', "ion-inlining", "on/off",
                               "Inline methods where possible (default: on, off to disable)")
        || !op.addStringOption('\0', "ion-osr", "on/off",
                               "On-Stack Replacement (default: on, off to disable)")
        || !op.addStringOption('\0', "ion-limit-script-size", "on/off",
                               "Don't compile very large scripts (default: on, off to disable)")
        || !op.addIntOption('\0', "ion-uses-before-compile", "COUNT",
                            "Wait for COUNT calls or iterations before compiling "
                            "(default: 1000)", -1)
        || !op.addStringOption('\0', "ion-regalloc", "[mode]",
                               "Specify Ion register allocation:\n"
                               "  lsra: Linear Scan register allocation (default)\n"
                               "  backtracking: Priority based backtracking register allocation\n"
                               "  stupid: Simple block local register allocation")
        || !op.addBoolOption('\0', "ion-eager", "Always ion-compile methods (implies --baseline-eager)")
        || !op.addBoolOption('\0', "ion-compile-try-catch", "Ion-compile try-catch statements")
#ifdef JS_THREADSAFE
        || !op.addStringOption('\0', "ion-parallel-compile", "on/off",
                               "Compile scripts off thread (default: off)")
#endif
        || !op.addBoolOption('\0', "baseline", "Enable baseline compiler (default)")
        || !op.addBoolOption('\0', "no-baseline", "Disable baseline compiler")
        || !op.addBoolOption('\0', "baseline-eager", "Always baseline-compile methods")
        || !op.addIntOption('\0', "baseline-uses-before-compile", "COUNT",
                            "Wait for COUNT calls or iterations before baseline-compiling "
                            "(default: 10)", -1)
        || !op.addBoolOption('\0', "no-fpu", "Pretend CPU does not support floating-point operations "
                             "to test JIT codegen (no-op on platforms other than x86).")
        || !op.addBoolOption('\0', "fuzzing-safe", "Don't expose functions that aren't safe for "
                             "fuzzers to call")
#ifdef DEBUG
        || !op.addBoolOption('\0', "dump-entrained-variables", "Print variables which are "
                             "unnecessarily entrained by inner functions")
#endif
#ifdef JSGC_GENERATIONAL
        || !op.addBoolOption('\0', "no-ggc", "Disable Generational GC")
#endif
        )
    {
        return EXIT_FAILURE;
    }
    
    op.setArgTerminatesOptions("script", true);
    op.setArgCapturesRest("scriptArgs");
    
    switch (op.parseArgs(argc, (char**)argv)) {
        case OptionParser::ParseHelp:
            return EXIT_SUCCESS;
        case OptionParser::ParseError:
            op.printHelp(argv[0]);
            return EXIT_FAILURE;
        case OptionParser::Fail:
            return EXIT_FAILURE;
        case OptionParser::Okay:
            break;
    }
    
    op.printHelp("tt");
    
    if (op.getHelpOption())
        return EXIT_SUCCESS;
    
    testBuffer();
    
//    testBufferPerfermens();
    
    return 0;
}

