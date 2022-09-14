import java.time.LocalDate;

/**
 * @author refracta
 * @version 2021년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 자바프로그래밍
 * @file MonthlyWalkLog
 * 월별 걸음 거리 기록
 */
public class MonthlyWalkLog {
    private double[] dailyDistance = null;
    public final int year;
    public final int month;
    private LocalDate logDate;

    public MonthlyWalkLog() {
        logDate = LocalDate.now();
        this.year = logDate.getYear();
        this.month = logDate.getMonthValue();
        dailyDistance = new double[logDate.lengthOfMonth()];
    }

    public MonthlyWalkLog(int year, int month) throws MWInvalidTimeDataException {
        if (year < 2000) {
            throw new MWInvalidTimeDataException(String.format("The year value must be greater than or equal to 2000. year: %d", year));
        } else if (!(month >= 1 && month <= 12)) {
            throw new MWInvalidTimeDataException(String.format("The value of month must be between 1 and 12. month: %d", month));
        }
        // year, month 유효성 검사

        this.year = year;
        this.month = month;
        logDate = LocalDate.of(year, month, 1);
        dailyDistance = new double[logDate.lengthOfMonth()];
    }

    public void recordDistance(int day, double distance) throws MWInvalidParameterException {
        if (!(1 <= day && day < dailyDistance.length)) {
            throw new MWInvalidTimeDataException(String.format("The value of day must be between %d and %d. day: %d", 1, dailyDistance.length, day));
        } else if (distance < 0.0) {
            throw new MWInvalidDistanceException("The value of distance must be greater than zero.");
        }
        // day, distance 유효성 검사

        dailyDistance[day - 1] = distance;
    }

    public double getDistance(int day) throws MWInvalidDistanceException {
        if (!(1 <= day && day <= dailyDistance.length)) {
            throw new MWInvalidDistanceException(String.format("The value of day must be between %d and %d. day: %d", 1, dailyDistance.length, day));
        }
        // day 유효성 검사

        return dailyDistance[day - 1];
    }

    public void print() {
        String[] weekdays = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
        System.out.printf("%d년 %d월%n", year, month);
        for (var weekday : weekdays)
            System.out.printf("%10s ", weekday);
        System.out.println();
        int w = logDate.getDayOfWeek().ordinal();
        System.out.print(" ".repeat((w + 1) * 11));
        int day = 0;
        while (day < logDate.lengthOfMonth()) {
            System.out.printf("%10.2f ", dailyDistance[day]);
            ++day;
            w = (w + 1) % 7;
            if (w == 6) System.out.println();
        }
        System.out.println();
    }
}
