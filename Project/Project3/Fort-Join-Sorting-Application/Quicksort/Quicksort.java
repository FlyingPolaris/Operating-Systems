import java.util.concurrent.*;

public class Quicksort extends RecursiveAction {

    static final int THRESHOLD = 5;

    private int begin;
    private int end;
    private int[] array;

    public Quicksort(int begin, int end, int[] array) {
        this.begin = begin;
        this.end = end;
        this.array = array;
    }

    protected void compute() {
        if (end - begin < THRESHOLD) {
            for (int i = begin; i < end; ++i) {
                for (int j = begin; j < end; ++j) {
                    int tmp;
                    if (array[j] > array[j + 1]) {
                        tmp = array[j + 1];
                        array[j + 1] = array[j];
                        array[j] = tmp;
                    }
                }
            }
        } else {
            int tmp = array[begin];
            int i, j;
            i = begin;
            j = end;

            while (i != j) {
                while (j > i && array[j] >= tmp) {
                    --j;
                }
                if (i < j) {
                    array[i] = array[j];
                    ++i;
                }
                while (i < j && array[i] < tmp) {
                    ++i;
                }
                if (i < j) {
                    array[j] = array[i];
                    --j;
                }
            }
            array[i] = tmp;
            Quicksort leftTask = new Quicksort(begin, i - 1, array);
            Quicksort rightTask = new Quicksort(i + 1, end, array);

            leftTask.fork();
            rightTask.fork();
            leftTask.join();
            rightTask.join();
        }
    }

    public static void main(String[] args) {
        ForkJoinPool pool = new ForkJoinPool();
        int size = args.length;
        int[] array = new int[size];

        for (int i = 0; i < size; i++) {
            array[i] = Integer.parseInt(args[i]);
        }

        Quicksort task = new Quicksort(0, size - 1, array);
        pool.invoke(task);

        for (int i = 0; i < size; i++) {
            System.out.print(array[i] + " ");
        }
        System.out.println("");

    }
}
