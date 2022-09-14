import javafx.embed.swing.SwingFXUtils;
import javafx.scene.image.Image;
import javafx.scene.paint.Color;

import java.awt.image.BufferedImage;

public interface RenderUtility {

    /**
     * JavaFX 이미지를 받아 평균색을 산출하여 반환한다.
     * @param i JavaFX Image
     * @return Average Image Color
     */
    public static Color getAverageColor(Image i) {
        BufferedImage bi = SwingFXUtils.fromFXImage(i, null);
        int w = bi.getWidth();
        int h = bi.getHeight();
        int x0 = 0;
        int y0 = 0;
        int x1 = x0 + w;
        int y1 = y0 + h;
        long sumr = 0, sumg = 0, sumb = 0; //, suma = 0;
        for (int x = x0; x < x1; x++) {
            for (int y = y0; y < y1; y++) {
                int rgba = bi.getRGB(x, y);
                sumb += rgba & 0xff;
                sumg += (rgba & 0xff00) >> 8;
                sumr += (rgba & 0xff0000) >> 16;
                // (rgba & 0xff000000) >>> 24
                // suma += pixel.getOpacity();
            }
        }
        double num = w * h;
        return new Color(sumr / num / 255, sumg / num / 255, sumb / num / 255, 1);
    }

    /**
     * JavaFX Color 2개를 받아 합성색을 반환한다.
     * @param c0
     * @param c1
     * @return Merged JavaFX Color
     */
    public static Color mergedColor(Color c0, Color c1) {
        return new Color((c0.getRed() + c1.getRed()) / 2, (c0.getGreen() + c1.getGreen()) / 2, (c0.getBlue() + c1.getBlue()) / 2, (c0.getOpacity() + c1.getOpacity()) / 2);
    }
}
