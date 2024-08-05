
#include <jni.h>
#include "parafrost/src/cpu/solve.h"
#include "kodkod_engine_satlab_ParaFrost.h"

using namespace ParaFROST;
/*
 * Class:     kodkod_engine_satlab_ParaFrost
 * Method:    make
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_kodkod_engine_satlab_ParaFrost_make
  (JNIEnv *, jclass) {
        Solver *solver = new Solver("");
        return ((jlong) solver);
}

/*
 * Class:     kodkod_engine_satlab_ParaFrost
 * Method:    free
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_kodkod_engine_satlab_ParaFrost_free
  (JNIEnv *, jobject, jlong solver) {
        delete ((Solver*)solver);
}

/*
 * Class:     kodkod_engine_satlab_ParaFrost
 * Method:    addVariables
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_kodkod_engine_satlab_ParaFrost_addVariables
  (JNIEnv *, jobject, jlong solver, jint vars) {
        Solver *solverPtr = (Solver*) solver;
        for(int i = 0; i < vars; i++) {
                solverPtr->iadd();
        }
}

/*
 * Class:     kodkod_engine_satlab_ParaFrost
 * Method:    addClause
 * Signature: (J[I)Z
 */
JNIEXPORT jboolean JNICALL Java_kodkod_engine_satlab_ParaFrost_addClause
  (JNIEnv * env, jobject, jlong solver, jintArray clause) {
        jsize clauseLength = env->GetArrayLength(clause);
        jint *buf = env->GetIntArrayElements(clause, JNI_FALSE);
        Solver *solverPtr = ((Solver*)solver);
        Lits_t c, org;
        for (int i = 0; i<clauseLength; i++) {
                int var = *(buf+i);
                if (var > 0)
                        org.push(V2DEC(var, 0));
                else
                        org.push(V2DEC(-var, 1));        
        }
        if (solverPtr->itoClause(c,org)) {
                return JNI_TRUE;
        }
        else {
                solverPtr->learnEmpty();
                solverPtr->killSolver();
                return JNI_FALSE;
        }        
}

/*
 * Class:     kodkod_engine_satlab_ParaFrost
 * Method:    solve
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_kodkod_engine_satlab_ParaFrost_solve
  (JNIEnv *, jobject, jlong solver) {
        Solver *solverPtr = ((Solver*)solver);
        Lits_t lits;
        return solverPtr->isolve(lits);
}

/*
 * Class:     kodkod_engine_satlab_ParaFrost
 * Method:    valueOf
 * Signature: (JI)Z
 */
JNIEXPORT jboolean JNICALL Java_kodkod_engine_satlab_ParaFrost_valueOf
  (JNIEnv *, jobject, jlong solver, jint var) {
        Solver *solverPtr = ((Solver*)solver);
        return solverPtr->varValue(var);
}


