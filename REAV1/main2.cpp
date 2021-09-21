int main ()
{
    //################################################################################
    // RV1
    //################################################################################

    /* Q1 Gerar a imagem 512x512 "target.png", com circulos concentricos com intensidades crescentes de níveis de cinza.
     * 
    Mat imagem = Mat::zeros( 512, 512, CV_8UC3 );

    circle(imagem, Point(512/2,512/2), 110, Scalar(40,40,40), 240, LINE_AA);
    circle(imagem, Point(512/2,512/2), 90, Scalar(80,80,80), 200, LINE_AA);
    circle(imagem, Point(512/2,512/2), 70, Scalar(120,120,120), 160, LINE_AA);
    circle(imagem, Point(512/2,512/2), 50, Scalar(160,160,160), 120, LINE_AA);
    circle(imagem, Point(512/2,512/2), 30, Scalar(200,200,200), 60, LINE_AA);
    circle(imagem, Point(512/2,512/2), 10, Scalar(240,240,240), 20, LINE_AA);
    
    imshow("target", imagem);

    imwrite("target_isadora.png", imagem);
    //*/

    /* Q2 Gerar a imagem 512x512 "sinusoid.png", que contém uma senoide rotacionada de 30 graus e uma frequência 10mHz (supondo que os eixos representam frequência).

    imwrite("sinusoid_<aluno>.png", img);
    //*/

    /*// Q3 Carregue a imagem "lena.png" e adicione ruido sal e pimenta a ela,  resultando numa imagem similar a lena_sp.png.
     * 
    Mat imagem = imread("lena.png", CV_LOAD_IMAGE_GRAYSCALE);

    Mat saltpepper_noise = Mat::zeros(imagem.rows, imagem.cols,CV_8U);
    randu(saltpepper_noise,0,255);

    Mat black = saltpepper_noise < 30;
    Mat white = saltpepper_noise > 225;

    Mat saltpepper_imagem = imagem.clone();
    saltpepper_imagem.setTo(255,white);
    saltpepper_imagem.setTo(0,black);

    imshow("lena_sp", saltpepper_imagem);

    imwrite("lena_sp_isadora.png", saltpepper_imagem);
    //*/

    /*// Q4 Carregar a imagem "lena.png" e criar/aplicar o efeito Vignette, resultando aproximadamente na imagem "lena_vignette.png"
     * 
    Mat imagem = imread("lena.png", CV_LOAD_IMAGE_GRAYSCALE);

    Mat kernel_X = getGaussianKernel(imagem.cols, 100);
    Mat kernel_Y = getGaussianKernel(imagem.rows, 100);
    Mat kernel_X_transpose;
    transpose(kernel_X, kernel_X_transpose);
    Mat kernel = kernel_Y * kernel_X_transpose;

    Mat mask_v, proc_img;
    normalize(kernel, mask_v, 0, 1, NORM_MINMAX);
    imagem.convertTo(proc_img, CV_64F);
    multiply(mask_v, proc_img, proc_img);
    convertScaleAbs(proc_img, proc_img);
    imshow ("lena_vignette_isadora", proc_img);

    imwrite("lena_vignette_isadora.png", proc_img);
    //*/

    /*// Q5 mesclar ruído senoidal e sal e pimenta à imagem (grayscale) "lena.png" e aplicar uma filtragem no domínio da frequência para atenuar o ruído.
    //*/
}
