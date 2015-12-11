using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Windows.Storage.Pickers;
using Windows.Storage;
using foxitSDK;
// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

/*
PDF SDK DEFINE:

 @brief	No rotation. 
#define	FSCRT_PAGEROTATION_0		0
 @brief	Rotate 90 degrees in clockwise direction.
#define	FSCRT_PAGEROTATION_90		1
 @brief	Rotate 180 degrees in clockwise direction. 
#define	FSCRT_PAGEROTATION_180		2
 @brief	Rotate 270 degrees in clockwise direction. 
#define	FSCRT_PAGEROTATION_270		3

#define FSCRT_ERRCODE_SUCCESS					0
#define FSCRT_ERRCODE_ERROR						-1
typedef int						FS_RESULT;
*/


namespace pdf
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class renderPage : Page
    {
        public renderPage()
        {
            this.InitializeComponent();

            
            m_PDFFunction = new Inherited_PDFFunction();
            m_SDKDocument = new FSDK_Document();
            m_PDFDoc.pointer = 0;
            m_iCurPageIndex = 0;
            m_PDFPage.pointer = 0;
            m_fPageWidth = 0.0f;
            m_fPageHeight = 0.0f;

            m_iStartX = 0;
            m_iStartY = 0;
            m_iRenderAreaSizeX = 0;
            m_iRenderAreaSizeY = 0;
            m_iRotation = 0;

            m_dbScaleDelta = 0.05f;
            m_dbScaleFator = 1.0f;
            m_dbCommonFitWidthScale = 1.0f;
            m_dbCommonFitHeightScale = 1.0f;
            m_dbRotateFitWidthScale = 1.0f;
            m_dbRotateFitHeightScale = 1.0f;

            m_bFitWidth = false;
            m_bFitHeight = false;

            
            
        }
        
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            m_pPDFFile = e.Parameter as Windows.Storage.StorageFile;
            if(m_pPDFFile != null)
            {
                OpenPDFDocument(m_pPDFFile);
            }
        }

        private void OpenPDFDocument(Windows.Storage.StorageFile file)
        {
            if (file != null)
            {
                IAsyncOperation<Windows.Storage.FileProperties.BasicProperties> file_property = file.GetBasicPropertiesAsync();
                Windows.Storage.FileProperties.BasicProperties properties = file_property.GetResults();
                m_SDKDocument = new FSDK_Document();
                int result = m_SDKDocument.OpenDocumentAsync(file, (int)properties.Size, null).GetResults();
                if(result != 0)
                {
                    return;
                }
                m_PDFDoc.pointer = m_SDKDocument.m_hDoc.pointer;
                result = LoadPage(m_iCurPageIndex);
                if(result != 0)
                {
                    return;
                }
                m_dbScaleFator = (m_dbCommonFitWidthScale < m_dbCommonFitHeightScale) ? m_dbCommonFitWidthScale : m_dbCommonFitHeightScale;
                ShowPage();
                
            }
            else
            {
                //ShowErrorLog("Error: Fail to pick a valid PDF file.", ref new UICommandInvokedHandler(this, renderPage.ReturnCommandInvokedHandler));
                return;
            }
        }

        private int LoadPage(int iPageIndex)
        {// To load and parse page.
            int result = -1;
            if (m_PDFDoc.pointer == 0)
            {
                //ShowErrorLog("Error: No PDF document has been loaded successfully.", ref new UICommandInvokedHandler(this, &demo_view::renderPage::ReturnCommandInvokedHandler));
                return result;
            }

            if (m_PDFPage.pointer != 0)
            {
                m_PDFFunction.My_Page_Clear(m_PDFPage);
                m_PDFPage.pointer = 0;
            }
            result = m_SDKDocument.LoadPageSync(iPageIndex);
            if (0 == result)
            {
                m_PDFPage.pointer = m_SDKDocument.m_hPage.pointer;
                m_iCurPageIndex = iPageIndex;
                GetPageInfo();
            }
            else
            {
                //ShowErrorLog("Error: Fail to load and parse a page.", ref new UICommandInvokedHandler(this, &demo_view::renderPage::ReturnCommandInvokedHandler),true, ret);
                ;
            }
                

            return result;
        }

        public void GetPageInfo()
        {// To get page size and prepare some necessary data.
            if (m_PDFPage.pointer == 0)
            {
                //ShowErrorLog("Error: No PDF page has been loaded successfully.", ref new UICommandInvokedHandler(this, &demo_view::renderPage::ReturnCommandInvokedHandler));
                return;
            }
            int result = m_PDFFunction.My_Page_GetSize(m_PDFPage, out m_fPageWidth,out m_fPageHeight);
            if (result == 0)
            {
                double scrollViewerW = scroll_pdf.ActualWidth;
                double scrollViewerH = scroll_pdf.ActualHeight;

                m_dbCommonFitWidthScale = scrollViewerW / m_fPageWidth;
                m_dbCommonFitHeightScale = scrollViewerH / m_fPageHeight;

                m_dbRotateFitWidthScale = scrollViewerW / m_fPageHeight;
                m_dbRotateFitHeightScale = scrollViewerH / m_fPageWidth;
            }
        }

        public void ShowPage()
        {//To render PDF page, finally to the image control.	
         //Calculate render size.
            CalcRenderSize();
            PixelSource bitmap =  new PixelSource();
            bitmap.Width = (int)m_iRenderAreaSizeX;
            bitmap.Height = (int)m_iRenderAreaSizeY;
            Windows.Storage.Streams.IRandomAccessStreamWithContentType stream = m_SDKDocument.RenderPageAsync(bitmap, m_iStartX, m_iStartY, m_iRenderAreaSizeX, m_iRenderAreaSizeY, m_iRotation).GetResults();
            if (stream == null)
            {
                //ShowErrorLog("Error: Fail to render page.", ref new UICommandInvokedHandler(this, &demo_view::renderPage::ReturnCommandInvokedHandler),true, FSCRT_ERRCODE_ERROR);
                return;
            }
            Windows.UI.Xaml.Media.Imaging.BitmapImage bmpImage = new Windows.UI.Xaml.Media.Imaging.BitmapImage();
            bmpImage.SetSource(stream);
            image.Width = (int)m_iRenderAreaSizeX;
            image.Height = (int)m_iRenderAreaSizeY;
            image.Source = bmpImage;
            
        }
        
        public void CalcRenderSize()
        {// To calculate render size.
            if (1 == m_iRotation || 3 == m_iRotation)
            {
                if (m_bFitWidth)
                    m_dbScaleFator = m_dbRotateFitWidthScale;
                if (m_bFitHeight)
                    m_dbScaleFator = m_dbRotateFitHeightScale;

                m_iRenderAreaSizeX = (int)(m_fPageHeight * m_dbScaleFator);
                m_iRenderAreaSizeY = (int)(m_fPageWidth * m_dbScaleFator);
            }
            else
            {
                if (m_bFitWidth)
                    m_dbScaleFator = m_dbCommonFitWidthScale;
                if (m_bFitHeight)
                    m_dbScaleFator = m_dbCommonFitHeightScale;

                m_iRenderAreaSizeX = (int)(m_fPageWidth * m_dbScaleFator);
                m_iRenderAreaSizeY = (int)(m_fPageHeight * m_dbScaleFator);
            }
        }

        private Windows.Storage.StorageFile	        m_pPDFFile;
		private bool                                m_bReleaseLibrary;             // A flag used to indicate if SDK library has been initialized successfully and needs to be released.
        private FSDK_Document                       m_SDKDocument;
        private DocHandle                           m_PDFDoc;
		//FSCRT_DOCUMENT m_PDFDoc;           // SDK document handle of current loaded document.
        //FSCRT_PAGE m_PDFPage;              // SDK page handle of current loaded page.
        PageHandle                                  m_PDFPage;
        private int                                 m_iCurPageIndex;               //Index of current loaded page.
        private float                               m_fPageWidth;             // Page width of current page.
        private float                               m_fPageHeight;            // Page Height of current page.

        //used for rendering page;
        private int m_iStartX;
        private int m_iStartY;
        private int m_iRenderAreaSizeX;
        private int m_iRenderAreaSizeY;
        private int m_iRotation;

        //Used for zooming.
        private double m_dbScaleDelta;
        private double m_dbScaleFator;
        private double m_dbCommonFitWidthScale;
        private double m_dbCommonFitHeightScale;
        private double m_dbRotateFitWidthScale;
        private double m_dbRotateFitHeightScale;
        private bool m_bFitWidth;
        private bool m_bFitHeight;

        private Inherited_PDFFunction m_PDFFunction;

        private void Click_BTN_NextPage(object sender, RoutedEventArgs e)
        {

        }

        private void Click_BTN_ZoomIn(object sender, RoutedEventArgs e)
        {

        }

        private void Click_BTN_ZoomOut(object sender, RoutedEventArgs e)
        {

        }

        private void Click_BTN_FitHeight(object sender, RoutedEventArgs e)
        {

        }

        private void Click_BTN_FitWidth(object sender, RoutedEventArgs e)
        {

        }

        private void Click_BTN_ActualSize(object sender, RoutedEventArgs e)
        {

        }

        private void Click_BTN_RotateRight(object sender, RoutedEventArgs e)
        {

        }

        private void Click_BTN_RotateLeft(object sender, RoutedEventArgs e)
        {

        }

        private void Click_BTN_PrePage(object sender, RoutedEventArgs e)
        {

        }
    }
}
