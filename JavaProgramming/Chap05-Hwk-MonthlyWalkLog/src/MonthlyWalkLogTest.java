/**
 * @author refracta
 * @version 2021년도 2학기
 * @copyright 한국기술교육대학교 컴퓨터공학부 자바프로그래밍
 * @file MonthlyWalkLog
 * 월별 걸음 거리 기록 테스트 프로그램
 */
public class MonthlyWalkLogTest {

    public static void main(String[] args) throws MWInvalidParameterException {
        MonthlyWalkLog log = new MonthlyWalkLog();
        log.recordDistance(3, 5.5);
        log.print();

        // vm 매개변수로 -ea를 추가하여 테스트
        try {
            MonthlyWalkLog invalidYearLog = new MonthlyWalkLog(1999, 1);
        } catch (MWInvalidTimeDataException e) {
            assert "The year value must be greater than or equal to 2000. year: 1999".equals(e.getMessage());
        }

        try {
            MonthlyWalkLog invalidMonthLog = new MonthlyWalkLog(2021, -1);
        } catch (MWInvalidTimeDataException e) {
            assert "The value of month must be between 1 and 12. month: -1".equals(e.getMessage());
        }

        try {
            MonthlyWalkLog callDistanceWithInvalidDay = new MonthlyWalkLog();
            callDistanceWithInvalidDay.getDistance(-1);
        } catch (MWInvalidDistanceException e) {
            assert "The value of day must be between 1 and 31. day: -1".equals(e.getMessage());
        }

        try {
            MonthlyWalkLog callRecordDistanceWithInvalidDay = new MonthlyWalkLog();
            callRecordDistanceWithInvalidDay.recordDistance(0, 0.0);
        } catch (MWInvalidParameterException e) {
            assert "The value of day must be between 1 and 31. day: 0".equals(e.getMessage());
        }

        try {
            MonthlyWalkLog callRecordDistanceWithInvalidDistance = new MonthlyWalkLog();
            callRecordDistanceWithInvalidDistance.recordDistance(1, -1.0);
        } catch (MWInvalidParameterException e) {
            assert "The value of distance must be greater than zero.".equals(e.getMessage());
        }
    }
}
