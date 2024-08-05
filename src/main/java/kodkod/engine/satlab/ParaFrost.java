package kodkod.engine.satlab;

public class ParaFrost extends NativeSolver {

    public ParaFrost() {
        super(make());
    }

    static {
        loadLibrary(ParaFrost.class);
    }

    @Override
    public String toString() {
        return "parafrost";
    }

    private static native long make();

    @Override
    native void free(long peer);

    @Override
    native void addVariables(long peer, int numVariables);

    @Override
    native boolean addClause(long peer, int[] lits);

    @Override
    native boolean solve(long peer);

    @Override
    native boolean valueOf(long peer, int literal);
}
