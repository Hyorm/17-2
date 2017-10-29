// Date - 2017. 08. 29
// Author - HyeonUng Shin
// Read data from csv formatted file and parse to arff (Weka) file

import weka.core.Attribute;
import weka.core.DenseInstance;
import weka.core.Instances;

import weka.core.converters.ArffSaver;
import java.io.*;
import java.util.*;

public class Main {
    static final String[] genres = {"unknown", "Action", "Adventure", "Animation", "Children's", "Comedy", "Crime", "Documentary", "Drama", "Fantasy", "Film-Noir", "Horror", "Musical", "Mystery", "Romance", "Sci-Fi", "Thriller", "War", "Western"};

    public static void main(String[] args) throws IOException {
        LinkedList<HashMap<String, String>> ratings = new LinkedList<HashMap<String, String>>();
        HashMap<String, HashMap<String, String>> users = new HashMap<String, HashMap<String, String>>();
        HashMap<String, HashMap<String, String>> movies = new HashMap<String, HashMap<String, String>>();
        HashMap<String, HashMap<String, Double>> user_genre_avr = new HashMap<String, HashMap<String, Double>>();

        BufferedReader br;
        String row;

        // rating data parsing;  file format - (user_id   movie_id    rating  timestamp)
        br = new BufferedReader(new FileReader("data/ratings"));
        for(int i = 0; (row = br.readLine()) != null; i++) {
            String[] attr = row.split("\t");
            if(attr.length < 4) continue;

            HashMap<String, String> col = new HashMap<String, String>();

            col.put("user_id", attr[0]);
            col.put("movie_id", attr[1]);
            col.put("rating", attr[2]);

            ratings.add(col);
        }

        // user data parsing;   file format - (user_id  age gender  occupation  zipcode)
        br = new BufferedReader(new FileReader("data/reviewers"));
        while((row = br.readLine()) != null) {
            String[] attr = row.split("\t");
            if(attr.length < 5) continue;

            HashMap<String, String> col = new HashMap<String, String>();

            col.put("age", attr[1]);
            col.put("gender", attr[2]);
            col.put("occupation", attr[3]);
            col.put("zipcode", attr[4]);

            users.put(attr[0], col);
        }

        // movie data parsing;  file format - (movie_id release_date    video_release_date  IMDB_URL    genres ...)
        br = new BufferedReader(new FileReader("data/movies"));
        while((row = br.readLine()) != null) {
            String[] attr = row.split("\t");
            if(attr.length < 24) continue;

            HashMap<String, String> col = new HashMap<String, String>();

            col.put("title", attr[1]);
            col.put("release_date", attr[2]);
            col.put("video_release_date", attr[3]);
            col.put("IMDB_URL", attr[4]);

            for(int i = 0; i < genres.length; i++) {
                col.put(genres[i], attr[i + 5]);
            }

            movies.put(attr[0], col);
        }

        // make user-genre preference average table
        for(String user : users.keySet()) {
            int[] genreCount = new int[genres.length];
            HashMap<String, Double> genreAverageTable = new HashMap<String, Double>();

            for(int i = 0; i < genres.length; i++) {
                genreAverageTable.put(genres[i], 0.0);
            }

            for(HashMap<String, String> rating : ratings) {     // iterate all ratings
                if(rating.get("user_id").equals(user)) {
                    for(int i = 0; i < genres.length; i++) {
                        if(movies.get(rating.get( "movie_id" )).get(genres[i]).equals("1")) {
                            Double average = genreAverageTable.get(genres[i]);
                            Double rate = Double.parseDouble(rating.get("rating"));

                            genreAverageTable.put(genres[i], average + (rate - average) / ++genreCount[i]); // put cumulative average
                        }
                    }
                }
            }

            for(int i = 0; i < genreCount.length; i++) {
                if(genreCount[i] == 0) {
                    genreAverageTable.put(genres[i], 3.0);      // give median (1~5)
                }
            }

            user_genre_avr.put(user, genreAverageTable);
        }

        ArrayList<Attribute> features = new ArrayList<Attribute>(43);

        // set attributes
        features.add(0, new Attribute("rating"));
        features.add(1, new Attribute("age"));
        features.add(2, new Attribute("gender",(ArrayList<String>)null));
        features.add(3, new Attribute("occupation",(ArrayList<String>)null));
        features.add(4, new Attribute("year"));

        for(int i = 0; i < genres.length; i++) {
            features.add(i + 5, new Attribute(genres[i]));
        }

        for(int i = genres.length; i < genres.length * 2; i++) {
            features.add(i + 5, new Attribute(genres[i - genres.length] + "_avr"));
        }

        Instances wekaDataset = new Instances("MovieRatings", features, ratings.size());

        //  make row and insert
        double[] instanceValue = new double[wekaDataset.numAttributes()];
        for(HashMap rating : ratings){
            HashMap<String, String> user = users.get(rating.get("user_id"));        // get user data
            HashMap<String, String> movie = movies.get(rating.get("movie_id"));     // get movie data

            if(user == null || movie == null) continue;

            instanceValue[0] = Double.parseDouble(rating.get("rating").equals("5") ? "1" : "0");    // rating
            instanceValue[1] = Double.parseDouble(user.get("age")) < 10 ? 1 : Math.floor(Double.parseDouble(user.get("age")) / 10.0) * 10.0;  // aggregated age
            instanceValue[2] = wekaDataset.attribute(2).addStringValue(user.get("gender")); // gender
            instanceValue[3] = wekaDataset.attribute(3).addStringValue(user.get("occupation")); // occupation
            instanceValue[4] = Double.parseDouble(movie.get("release_date").split("-").length < 3 ? "1950" : String.valueOf(Math.floor(Double.valueOf(movie.get("release_date").split("-")[2]) / 10.0) * 10.0));  // year (aggregated)
            // instanceValue[4] = Double.parseDouble(movie.get("release_date").split("-").length < 3 ? "1950" : movie.get("release_date").split("-")[2]);  // year (raw)

            for(int i = 0; i < genres.length; i++) {    // genres
                instanceValue[i + 5] = Double.parseDouble(movie.get(genres[i]));
            }

            for(int i = genres.length; i < genres.length * 2; i++) {    // genre average values
                instanceValue[i + 5] = user_genre_avr.get(rating.get("user_id")).get(genres[i - genres.length]);
            }

            wekaDataset.add(new DenseInstance(1.0, instanceValue.clone()));     // insert
        }

        ArffSaver saver = new ArffSaver();

        saver.setInstances(wekaDataset);
        saver.setFile(new File("data/matrix.arff"));
        saver.writeBatch();
    }
}
