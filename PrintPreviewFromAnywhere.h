// **************************************************
// Custom code for CustomerTrackerForm
// Created: 04/08/2016 10:33:15 AM
// **************************************************
using System;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Windows.Forms;
using Erp.Adapters;
using Erp.UI;
using Ice.Lib;
using Ice.Adapters;
using Ice.Lib.Customization;
using Ice.Lib.ExtendedProps;
using Ice.Lib.Framework;
using Ice.Lib.Searches;
using Ice.UI.FormFunctions;
 
//ADDED THESE
using Ice.Core;
 
//CUSTOM ASSEMBLIES - Tools > Assembly Reference Manager > Add Custom Reference
//Erp.Contracts.Rpt.ARInvForm
//Erp.UIRpt.ARInvForm
//Ice.Core.Session
 
public class Script
{
    // ** Wizard Insert Location - Do Not Remove 'Begin/End Wizard Added Module Level Variables' Comments! **
    // Begin Wizard Added Module Level Variables **
 
    // End Wizard Added Module Level Variables **
 
    // Add Custom Module Level Variables Here **
 
    public void InitializeCustomCode()
    {
        // ** Wizard Insert Location - Do not delete 'Begin/End Wizard Added Variable Initialization' lines **
        // Begin Wizard Added Variable Initialization
 
        // End Wizard Added Variable Initialization
 
        // Begin Wizard Added Custom Method Calls
 
        this.Invoices_ALL_PDF_btn.Click += new System.EventHandler(this.Invoices_ALL_PDF_btn_Click);
        this.Invoices_CLOSED_PDF_btn.Click += new System.EventHandler(this.Invoices_CLOSED_PDF_btn_Click);
        this.Invoices_OPEN_PDF_btn.Click += new System.EventHandler(this.Invoices_OPEN_PDF_btn_Click);
        // End Wizard Added Custom Method Calls
    }
 
    public void DestroyCustomCode()
    {
        // ** Wizard Insert Location - Do not delete 'Begin/End Wizard Added Object Disposal' lines **
        // Begin Wizard Added Object Disposal
 
        this.Invoices_ALL_PDF_btn.Click -= new System.EventHandler(this.Invoices_ALL_PDF_btn_Click);
        this.Invoices_CLOSED_PDF_btn.Click -= new System.EventHandler(this.Invoices_CLOSED_PDF_btn_Click);
        this.Invoices_OPEN_PDF_btn.Click -= new System.EventHandler(this.Invoices_OPEN_PDF_btn_Click);
        // End Wizard Added Object Disposal
 
        // Begin Custom Code Disposal
 
        // End Custom Code Disposal
    }
 
    private void Invoices_ALL_PDF_btn_Click(object sender, System.EventArgs args)
    {
        // ** Place Event Handling Code Here **
 
       //EpidataView Function to determine which invoice you have highlighted
        EpiDataView EDV = (EpiDataView)oTrans.EpiDataViews["InvAll"];
     
        previewInvoice(Convert.ToInt32(EDV.dataView[EDV.Row]["InvoiceNum"]));
     
    }
 
    private void Invoices_CLOSED_PDF_btn_Click(object sender, System.EventArgs args)
    {
        // ** Place Event Handling Code Here **
 
       //EpidataView Function to determine which invoice you have highlighted
        EpiDataView EDV = (EpiDataView)oTrans.EpiDataViews["InvClose"];
     
        previewInvoice(Convert.ToInt32(EDV.dataView[EDV.Row]["InvoiceNum"]));
 
    }
 
    private void Invoices_OPEN_PDF_btn_Click(object sender, System.EventArgs args)
    {
        // ** Place Event Handling Code Here **
 
       //EpidataView Function to determine which invoice you have highlighted
        EpiDataView EDV = (EpiDataView)oTrans.EpiDataViews["InvOpen"];
     
        previewInvoice(Convert.ToInt32(EDV.dataView[EDV.Row]["InvoiceNum"]));
 
    }   
     
private void previewInvoice(int invcNum)
    {
        //This custom function takes an invoice number and calls the AR Invcoice Adapter to launch a pdf preview of the invoice
     
        //Invoke the BO
        ARInvFormAdapter ar = new ARInvFormAdapter(oTrans);
        ar.BOConnect();
         
        //Get Paramters
        ar.GetNewParameters();
 
        //Set Parameters 
    //Change your ReportStyleNum to match your report style in Epicor
        ar.ReportData.ARInvFormParam[0].InvoiceNum = invcNum;
        ar.ReportData.ARInvFormParam[0].ReportStyleNum = 1001;
        ar.ReportData.ARInvFormParam[0].AutoAction = "SSRSPREVIEW";
        ar.ReportData.ARInvFormParam[0].SSRSRenderFormat = "PDF";
        ar.ReportData.ARInvFormParam[0].AgentID= "SystemTaskAgent";
        ar.ReportData.ARInvFormParam[0].WorkstationID = Ice.Lib.Report.EpiReportFunctions.GetWorkStationID((Ice.Core.Session)oTrans.Session);
 
        //Submit to Agent
        ar.SubmitToAgent("SystemTaskAgent",0,0);
    }
 
}
