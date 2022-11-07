import java.util.concurrent.ThreadLocalRandom;
import javafx.animation.PauseTransition;
import javafx.animation.TranslateTransition;
import javafx.application.Platform;
import javafx.scene.Group;
import javafx.scene.paint.Color;
import javafx.scene.shape.Line;
import javafx.util.Duration;
/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @version 2022년도 2학기 
 * @author 김상진
 * 팩토리 메소드 패턴: Asteroid
 * UserShip.java: 사용자 우주선
 */
public class UserShip extends Group {
	private double centerX;
	private double centerY;
	private double x;
	private double y;
	private double targetX;
	private double targetY;
	private double angle = 0;
	private double theta = 0;
	private boolean isMoving = false;
	private boolean hasCrashed = false;
	Line line4 = null;
	Line line5 = null;
	private TranslateTransition moveTransition = new TranslateTransition();
	public UserShip() {
		moveTransition.setNode(this);
		init();
	}
	public void init() {
		getChildren().clear();
		setTranslateX(0d);
		setTranslateY(0d);
		isMoving = false;
		hasCrashed = false;
		centerX = Utility.initLoc.x();
		centerY = Utility.initLoc.y()+10;
		x = Utility.initLoc.x(); // 250
		y = Utility.initLoc.y(); // 240
		angle = 0;
		adjustTheta();
		Line line1 = new Line(x,y,x-10,y+20);
		Line line2 = new Line(x,y,x+10,y+20);
		Line line3 = new Line(x-5,y+14,x+5,y+14);
		line4 = new Line(x-3,y+14,x,y+18);
		line5 = new Line(x+3,y+14,x,y+18);
		
		line1.setStroke(Color.WHITE);
		line2.setStroke(Color.WHITE);
		line3.setStroke(Color.WHITE);
		line4.setStroke(Color.BLACK);
		line5.setStroke(Color.BLACK);
		line1.setStrokeWidth(3);
		line2.setStrokeWidth(3);
		line3.setStrokeWidth(3);
		
		line4.setStrokeWidth(3);
		line5.setStrokeWidth(3);
		getChildren().addAll(line1, line2, line4, line5, line3);
	}
	
	public boolean isMoving() {
		return isMoving;
	}
	public boolean hasCrashed() {
		return hasCrashed;
	}
	private void adjustTheta() {
		theta = angle-90;
		if(theta<0) theta += 360;
		theta *= Utility.radian;
	}
	private void rotate() {
		adjustTheta();
		x = centerX + 10*Math.cos(theta);
		y = centerY + 10*Math.sin(theta);
		//System.out.printf("theta (%.2f), rotate (%.2f, %.2f)%n", theta, x, y);
	}
	public void changeAngle(double d) {
		if(d<0&&angle== 0) angle=360;
		angle += d;
		if(angle==360) angle = 0;
		rotate();
	}
	public double getTheta() {
		return theta;
	}
	public Location getCurrentLoc() {
		return new Location(x, y);
	}
	public Location computeTarget() {
		double a = (x==centerX)? 0: (y-centerY)/(x-centerX);
		double b = y - a*x;
		
		if(angle>-45&&angle<=45) {
			targetY = -10d;
			targetX = (a==0)? x: -b/a;
		}
		else if(angle>45&&angle<=135) {
			targetX = 510d;
			targetY = a*targetX + b;
		}
		else if(angle>135&&angle<=225) {
			targetY = 510d;
			targetX = (a==0)? x: (targetY-b)/a;
		}
		else {
			targetX = -10d;
			targetY = b;
		}
		return new Location(targetX, targetY);
		//System.out.printf("angle=%.2f, a = %.2f, b = %.2f, (%.2f, %.2f)%n", angle, a, b, targetX, targetY);
	}
	public void checkAndMove() {
		if(x>0&&x<500&&y>0&&y<500) return;
		if(y<=0) {
			y=500d;
			x=500d-x;
		}
		else if(x<=0) {
			x=500d;
			y=500d-y;
		}
		else if(x>=500) {
			x=0d;
			y=500d-y;
		}
		else if(y>=500) {
			y=0d;
			x=500d-x;
		}
		setTranslateX(x-Utility.initLoc.x());
		setTranslateY(y-Utility.initLoc.y());
		Platform.runLater(new Runnable() {
            @Override public void run() {
            	move();
            }
		});
	}
	public void realign() {
		x = Utility.initLoc.x()+getTranslateX();
		y = Utility.initLoc.y()+getTranslateY();
		centerX = Utility.initLoc.x()+getTranslateX();
		centerY = Utility.initLoc.y()+10+getTranslateY();
		rotate();
	}
	public void move() {
		isMoving = true;
		line4.setStroke(Color.WHITE);
		line5.setStroke(Color.WHITE);
		PauseTransition thrustTransition = new PauseTransition(Duration.millis(200d));
		thrustTransition.setOnFinished(e->{
			line4.setStroke(Color.BLACK);
			line5.setStroke(Color.BLACK);
		});
		thrustTransition.play();
		Duration duration = Duration.millis(Utility.getDistance(getCurrentLoc(),computeTarget())*10);
		moveTransition.setDuration(duration);
		//System.out.printf("move theta (theta = %.2f)%n", theta);
		//System.out.printf("move coordinate (%.2f, %.2f), (%.2f, %.2f)%n", x, y, targetX, targetY);
		//System.out.printf("move translate (%.2f, %.2f)%n", getTranslateX(), getTranslateY());
		moveTransition.setByX(targetX-x);
		moveTransition.setByY(targetY-y);
		moveTransition.setCycleCount(1);
		moveTransition.setOnFinished(e->{
			realign();
			checkAndMove();
			isMoving = false;
		});		
		moveTransition.play();
	}
	public void stop() {
		isMoving = false;
		moveTransition.stop();
		line4.setStroke(Color.BLACK);
		line5.setStroke(Color.BLACK);
		//System.out.printf("stop theta (theta = %.2f)%n", theta);
		//System.out.printf("stop coordinate (%.2f, %.2f), (%.2f, %.2f)%n", x, y, targetX, targetY);
		//System.out.printf("stop translate (%.2f, %.2f)%n", getTranslateX(), getTranslateY());
		realign();
	}
	public void explode() {
		for(var line: getChildren()) {
			double delta = ThreadLocalRandom.current().nextInt(20);
			line.setTranslateX(line.getTranslateX()-delta);
			line.setTranslateY(line.getTranslateY()-delta);
		}
		hasCrashed = true;
	}
	public void jump() {
		int X = ThreadLocalRandom.current().nextInt(200);
		int Y = ThreadLocalRandom.current().nextInt(200);
		if(ThreadLocalRandom.current().nextBoolean()) X = -X;
		if(ThreadLocalRandom.current().nextBoolean()) Y = -Y;
		setTranslateX(X);
		setTranslateY(Y);
		realign();
	}
}

