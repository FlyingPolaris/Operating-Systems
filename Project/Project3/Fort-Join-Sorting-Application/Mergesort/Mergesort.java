import java.util.concurrent.*;

public class Mergesort extends RecursiveAction {

    static final int THRESHOLD = 5;

    private int begin;
    private int end;
    private int[] array;

    public Mergesort(int begin, int end, int[] array) {
        this.begin = begin;
        this.end = end;
        this.array = array;
    }

    public static void Merge(int[] array, int left, int midd, int right) {

        int a = left, b = midd;
        int i = 0;
        int[] tmp = new int[right - left + 1];
        while (a < midd && b <= right) {
            if (array[a] <= array[b]) {
                tmp[i] = array[a];
                i++;
                a++;
            } else {
                tmp[i] = array[b];
                i++;
                b++;
            }
        }
        while (a < midd) {
            tmp[i] = array[a];
            i++;
            a++;
        }
        while (b <= right) {
            tmp[i] = array[b];
            i++;
            b++;
        }
        for (int k = 0; k < i; ++k) {
            array[left + k] = tmp[k];
        }
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
            int mid = (begin + end) / 2;
            Mergesort left = new Mergesort(begin, mid, array);
            Mergesort right = new Mergesort(mid + 1, end, array);
            left.fork();
            right.fork();
            left.join();
            right.join();
            Merge(array, begin, mid + 1, end);
        }
    }

    public static void main(String[] args) {
        ForkJoinPool pool = new ForkJoinPool();
        int size = args.length;
        int[] array = new int[size];

        for (int i = 0; i < size; i++) {
            array[i] = Integer.parseInt(args[i]);
        }

        Mergesort task = new Mergesort(0, size - 1, array);
        pool.invoke(task);

        for (int i = 0; i < size; i++) {
            System.out.print(array[i] + " ");
        }
        System.out.println("");

    }
}
