package GeneticAlgorithm;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;

//Genetic Algorithm Heterogeneous Group Formation
public class GAHG {
    private int N, K, M, P;
    private double[][] marks;
    private ArrayList<Chromosome> chromosomes;

    public GAHG(int N, int K, int M, int P) {
        this.N = N;
        this.K = K;
        this.M = M;
        this.P = P;
        marks = new double[N][M];
        chromosomes = new ArrayList<>(P);
    }

    public static void test() {
        int N = 16;
        int K = 3;
        int M = 2;

        double[][] marks = new double[N][M];
        marks[0][0] = 3.0;
        marks[0][1] = 2.5;

        marks[1][0] = 3.5;
        marks[1][1] = 2.0;

        marks[2][0] = 0.5;
        marks[2][1] = 1.0;

        marks[3][0] = 2.0;
        marks[3][1] = 2.0;

        marks[4][0] = 1.5;
        marks[4][1] = 3.0;

        marks[5][0] = 0.5;
        marks[5][1] = 4.0;

        marks[6][0] = 1.1;
        marks[6][1] = 2.0;

        marks[7][0] = 3.4;
        marks[7][1] = 3.7;

        marks[8][0] = 1.5;
        marks[8][1] = 2.6;

        marks[9][0] = 4.0;
        marks[9][1] = 3.9;

        marks[10][0] = 3.1;
        marks[10][1] = 1.8;

        marks[11][0] = 1.8;
        marks[11][1] = 1.0;

        marks[12][0] = 0.5;
        marks[12][1] = 3.9;

        marks[13][0] = 2.7;
        marks[13][1] = 1.2;

        marks[14][0] = 2.1;
        marks[14][1] = 2.4;

        marks[15][0] = 3.6;
        marks[15][1] = 3.2;

        int[] order = {3, 1, 3, 2, 3, 2, 3, 1, 2, 3, 1, 2, 2, 1, 1, 2};

        GAHG test = new GAHG(N, K, M, 10);
        test.setMarks(marks);

        Chromosome chromosome = Chromosome.build(order, N, K, M, marks);
        System.out.println(chromosome);
    }

    public static void main(String... args) {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        try {
            System.out.print("Enter no. of students (N) : ");
            int N = Integer.parseInt(br.readLine());

            System.out.print("Enter no. of groups (K) : ");
            int K = Integer.parseInt(br.readLine());

            System.out.print("Enter no. of attributes (M) : ");
            int M = Integer.parseInt(br.readLine());

            GAHG gaGroups = new GAHG(N, K, M, 500);

            System.out.print("Enter minimum marks : ");
            double min = Double.parseDouble(br.readLine());

            System.out.print("Enter maximum marks : ");
            double max = Double.parseDouble(br.readLine());

            gaGroups.initMarks(min, max);
            gaGroups.printMarks();

            gaGroups.generatePopulation();

            int i = 50;
            gaGroups.iterate(i);
            gaGroups.getChromosomes().get(0).printChromosome();

            //for(int j = 0 ; j < gaGroups.getChromosomes().size() ; ++j)
            System.out.println("Overall Fitness value : " + gaGroups.getChromosomes().get(0).getFitnessValue());
        } catch (IOException ignored) {

        }
        //test();
    }

    public void initMarks(double min, double max) {
        for (int i = 0; i < N; ++i)
            marks[i] = RandomGenerators.getRandomArray(M, min, max);

        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j) marks[i][j] = ((Math.round(marks[i][j] * 100.0)) / 100.0);
    }

    private Chromosome buildRandomChromosome() {
        int[] order = RandomGenerators.randomDivide(N, K);
        return Chromosome.build(order, N, K, M, marks);
    }

    public void generatePopulation() {
        while (chromosomes.size() != P) chromosomes.add(buildRandomChromosome());
    }

    public void iterate(int limit) {
        int i = 1;
        while (i++ <= limit) {
            int a = RandomGenerators.getRandomInt(0, chromosomes.size());
            int b = RandomGenerators.getRandomInt(0, chromosomes.size());

            if (a == b) b = (b + 1) % chromosomes.size();

            Chromosome A = chromosomes.get(a);
            Chromosome B = chromosomes.get(b);
            Chromosome dupA = A.duplicate();
            Chromosome dupB = B.duplicate();

            Chromosome.crossover(dupA, dupB, N, K, M, marks);

            chromosomes.add(dupA);
            chromosomes.add(dupB);
            chromosomes.add(A);
            chromosomes.add(B);
            Collections.sort(chromosomes);

            setChromosomes(limitToSize(chromosomes, P));
        }
    }

    private ArrayList<Chromosome> limitToSize(ArrayList<Chromosome> chromosomes, int P) {
        if (chromosomes.size() > P) {
            while (chromosomes.size() != P) {
                chromosomes.remove(P);
            }
        }
        return chromosomes;
    }

    private void printMarks() {
        for (int i = 0; i < N; ++i)
            System.out.println("Student " + (i + 1) + " : " + Arrays.toString(marks[i]));
        System.out.println();
    }

    public ArrayList<Chromosome> getChromosomes() {
        return chromosomes;
    }

    public void setChromosomes(ArrayList<Chromosome> chromosomes) {
        this.chromosomes = chromosomes;
    }

    public double[][] getMarks() {
        return marks;
    }

    public void setMarks(double[][] marks) {
        this.marks = marks;
    }
}

class Chromosome implements Comparable<Chromosome> {
    private double[][] groups;
    private int[] order;
    private double fitness;

    public Chromosome() {
        fitness = 0.0;
    }

    public Chromosome(int N, int K, int M) {
        order = new int[N];
        groups = new double[K][M];
        fitness = 0;
    }

    private static void addArray(double[] arr1, double[] arr2) {
        for (int i = 0; i < arr1.length; ++i) arr1[i] += arr2[i];
    }

    public static Chromosome build(int[] order, int N, int K, int M, double[][] marks) {
        Chromosome chromosome = new Chromosome(N, K, M);
        int[] counts = new int[K];
        Arrays.fill(counts, 0);

        double[][] sum = new double[K][M];
        for (int j = 0; j < K; ++j) Arrays.fill(sum[j], 0);

        for (int j = 0; j < N; ++j) {
            addArray(sum[order[j] - 1], marks[j]);
            counts[order[j] - 1]++;
        }

        for (int j = 0; j < K; ++j)
            for (int k = 0; k < M; ++k)
                sum[j][k] /= counts[j];

        chromosome.setOrder(order);
        chromosome.setGroups(sum);
        chromosome.calculateFitness();
        return chromosome;
    }

    public static void crossover(Chromosome A, Chromosome B, int N, int K, int M, double[][] marks) {
        int[] orderA = A.getOrder();
        int[] orderB = B.getOrder();

        assert orderA.length == orderB.length;
        int start = RandomGenerators.getRandomInt(0, orderA.length / 2);
        int end = RandomGenerators.getRandomInt(orderA.length / 2, orderA.length);

        //System.out.println("Start : " + start + ", End : " + end);
        while (start <= end) {
            int temp = orderA[start];
            orderA[start] = orderB[start];
            orderB[start] = temp;

            ++start;
        }

        A = Chromosome.build(orderA, N, K, M, marks);
        B = Chromosome.build(orderB, N, K, M, marks);
    }

    private double calculateFitness(double[] arr1, double[] arr2) {
        double temp = 0.0;
        for (int i = 0; i < arr1.length; ++i) temp += Math.pow(arr1[i] - arr2[i], 2);
        return Math.sqrt(temp);
    }

    public void calculateFitness() {
        fitness = 0.0;
        for (int i = 0; i < groups.length; ++i)
            for (int j = i + 1; j < groups.length; ++j)
                fitness += calculateFitness(groups[i], groups[j]);

        fitness = Math.round(fitness * 100.0) / 100.0;
    }

    public Chromosome duplicate() {
        Chromosome chromosome = new Chromosome();
        chromosome.setOrder(this.getOrder());
        chromosome.setGroups(this.getGroups());
        chromosome.setFitnessValue(this.getFitnessValue());

        return chromosome;
    }

    public double getFitnessValue() {
        return fitness;
    }

    public void setFitnessValue(double fitness) {
        this.fitness = fitness;
    }

    public double[][] getGroups() {
        return groups;
    }

    public void setGroups(double[][] groups) {
        this.groups = groups;
    }

    @Override
    public int compareTo(Chromosome chromosome) {
        return Double.compare(fitness, chromosome.getFitnessValue());
    }

    public int[] getOrder() {
        return order;
    }

    public void setOrder(int[] order) {
        this.order = order;
    }

    public String toString() {
        return Arrays.toString(order) + ", Fitness value : " + fitness;
    }

    public void printChromosome() {
        HashMap<Integer, ArrayList<Integer>> map = new HashMap<>();

        for (int i = 0; i < order.length; ++i) {
            ArrayList<Integer> list = map.get(order[i]);
            if (list == null) list = new ArrayList<>();
            list.add(i + 1);
            map.put(order[i], list);
        }

        for (Integer in : map.keySet()) {
            String s = map.get(in).toString();
            System.out.println("Group " + in + " : " + s.substring(1, s.length() - 1));
        }
    }
}
