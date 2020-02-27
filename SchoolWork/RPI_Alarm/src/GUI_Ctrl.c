/*****************************************************
 * Title:       User Interface
 * Author:      
 * Date:        2/15/20
 * Class:       CISP 2410
 *
 * Description:
 *  ! This header file contains all of the function
 *  ! Declarations and definitions for the GUI
 *  ! Everything involving the GUI will be in
 *    --> this header
 *
 *****************************************************/



#include <gtk/gtk.h>        // For gtk stuff
#include <stdlib.h>         // Standard Library
#include "GUI_Ctrl.h"       // Prototypes
#include "Alarm.h"          // Alarm Functions
#include "ARM.h"



/* Private Functions */
static void UpdateLcdDisplay(char keyPadValue);
static void ClearLcdDisplay(void);
static void UpdateDisplay(void);
/***********************************/

// Global Variables
/***********************************/
// Labels
GtkWidget *g_Lbl_Lcd;
GtkWidget *g_Lbl_Status;

// Buttons
GtkWidget *g_Btn_Arm;
GtkWidget *g_Btn_Login;
GtkWidget *g_Btn_Zone1;
GtkWidget *g_Btn_Zone2;
GtkWidget *g_Btn_Zone3;
/***********************************/

const int INPUT_LIMIT = 6;

char sysStatusText[100] = {0x0};
char inputBuffer[6] = {0x0};
int zoneBtnStates[3] = {0,0,0};
int charCounter = 0;



/*****************************************************
 * ! Initializes all of the GUI elements
 * ! Adds CSS attributes to GUI elements
 * ! Also handles the formatting of text 
 *****************************************************/
void GUI_INIT(int argc, char* argv[])
{
    GtkBuilder  *builder; 
    GtkWidget   *window;
    GtkCssProvider *cssProvider;

    // Setup CSS
    cssProvider = gtk_css_provider_new ();
    gtk_css_provider_load_from_path(cssProvider,"UI/style.css",NULL);

    gtk_init(&argc, &argv);

    // XML Data File Pointer
    builder = gtk_builder_new_from_file("UI/HelloWorld.glade");

    // Main Window Pointer
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);
    
    // GUI Label Pointers
    g_Lbl_Lcd = GTK_WIDGET(gtk_builder_get_object(builder, "Lbl_Lcd"));
    g_Lbl_Status = GTK_WIDGET(gtk_builder_get_object(builder, "Lbl_Instruction"));
    
    // GUI Button Pointers
    g_Btn_Arm = GTK_WIDGET(gtk_builder_get_object(builder, "btnArm"));
    g_Btn_Login = GTK_WIDGET(gtk_builder_get_object(builder, "btnLogin"));
    g_Btn_Zone1 = GTK_WIDGET(gtk_builder_get_object(builder, "btn_Z1"));
    g_Btn_Zone2 = GTK_WIDGET(gtk_builder_get_object(builder, "btn_Z2"));
    g_Btn_Zone3 = GTK_WIDGET(gtk_builder_get_object(builder, "btn_Z3"));

    // Align Text Right
    gtk_label_set_xalign (GTK_LABEL(g_Lbl_Lcd), 1);
    // Align Text Left
    gtk_label_set_xalign (GTK_LABEL(g_Lbl_Status), 0);
    

    // Apply CSS
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);


    // Finish setup and start GUI
    g_object_unref(builder);
    gtk_widget_show(window);    
    UpdateDisplay();           
    gtk_main();
    return;
}



// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}



/* Update all labels on screen */
static void UpdateDisplay(void)
{
    ClearLcdDisplay();
    GetSysStat(sysStatusText);
    gtk_label_set_text(GTK_LABEL(g_Lbl_Status), sysStatusText);
    return;
}



/* Update LCD label only (usr input) */
static void UpdateLcdDisplay(char keyPadValue)
{
    if (charCounter >= INPUT_LIMIT)
        ClearLcdDisplay();
    else
    {
        inputBuffer[charCounter] = keyPadValue;
        charCounter++;
        gtk_label_set_text(GTK_LABEL(g_Lbl_Lcd), inputBuffer);
    }
    
    return;
}



/*********************************************** 
 * Clear contents of inputBuffer variable
 * and update LCD label
 **********************************************/
static void ClearLcdDisplay(void)
{
    memset(inputBuffer, 0, 6);
    charCounter = 0;
    gtk_label_set_text(GTK_LABEL(g_Lbl_Lcd), "XXXXXX");
    return;
}




/*------------------ EVENT HANDLERS ------------------*/

void on_btn0_clicked(void)      {UpdateLcdDisplay('0');}
void on_btn1_clicked(void)      {UpdateLcdDisplay('1');}
void on_btn2_clicked(void)      {UpdateLcdDisplay('2');}
void on_btn3_clicked(void)      {UpdateLcdDisplay('3');}
void on_btn4_clicked(void)      {UpdateLcdDisplay('4');}
void on_btn5_clicked(void)      {UpdateLcdDisplay('5');}
void on_btn6_clicked(void)      {UpdateLcdDisplay('6');}
void on_btn7_clicked(void)      {UpdateLcdDisplay('7');}
void on_btn8_clicked(void)      {UpdateLcdDisplay('8');}
void on_btn9_clicked(void)      {UpdateLcdDisplay('9');}
void on_btnClear_clicked(void)  {ClearLcdDisplay();}
void on_btnEnter_clicked(void)   {UpdateDisplay();}

void on_btnLogin_clicked(void)
{
    if (LoginLogout(inputBuffer))
        gtk_button_set_label(GTK_BUTTON(g_Btn_Login), "LOGOUT");
    else
        gtk_button_set_label(GTK_BUTTON(g_Btn_Login), "LOGIN");

    UpdateDisplay(); 
    return;
}

void on_btnArm_clicked(void)
{
    if (ArmDisarm())
        gtk_button_set_label(GTK_BUTTON(g_Btn_Arm), "DISARM");
    else
        gtk_button_set_label(GTK_BUTTON(g_Btn_Arm), "ARM");
        
    UpdateDisplay();
    return;
}

void on_btn_Z1_toggled(void)
{
    printf("Login Status: %d\n", GetLoginStatus());
    if (!GetLoginStatus()) return;

    if (zoneBtnStates[0] == 0)
    {
        gtk_button_set_label(GTK_BUTTON(g_Btn_Zone1), "ON");
        zoneBtnStates[0] = 1;
    }
    else
    {
        gtk_button_set_label(GTK_BUTTON(g_Btn_Zone1), "OFF");
        zoneBtnStates[0] = 0;
    }
        
    return;
}

void on_btn_Z2_toggled(void)
{
    if (!GetLoginStatus()) return;

    if (zoneBtnStates[1] == 0)
    {
        gtk_button_set_label(GTK_BUTTON(g_Btn_Zone2), "ON");
        zoneBtnStates[1] = 1;
    }
    else
    {
        gtk_button_set_label(GTK_BUTTON(g_Btn_Zone2), "OFF");
        zoneBtnStates[1] = 0;
    }
    return;
}

void on_btn_Z3_toggled(void)
{
    if (!GetLoginStatus()) return;

    if (zoneBtnStates[2] == 0)
    {
        gtk_button_set_label(GTK_BUTTON(g_Btn_Zone3), "ON");
        zoneBtnStates[2] = 1;
    }
    else
    {
        gtk_button_set_label(GTK_BUTTON(g_Btn_Zone3), "OFF");
        zoneBtnStates[2] = 0;
    }
    return;
}

