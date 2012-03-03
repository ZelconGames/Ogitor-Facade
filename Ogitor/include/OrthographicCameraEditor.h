#pragma once
#include "BaseEditor.h"
#include "CameraEditor.h"

#include "OgitorsView.h"

namespace Ogitors
{ 
    class OgitorExport COrthographicCameraEditor : public CCameraEditor
    {
    public:
        friend class COrthographicCameraEditorFactory;
         virtual TiXmlElement* exportDotScene(TiXmlElement *pParent);
         
         virtual bool load(bool async = true);
         virtual void setViewMode(int value);
        
    protected:
        COrthographicCameraEditor(CBaseEditorFactory* factory) : CCameraEditor(factory){};
    };
    
   class OgitorExport COrthographicCameraEditorFactory: public CCameraEditorFactory
    {
    public:
        /**
        * Constructor
        */
        COrthographicCameraEditorFactory(OgitorsView *view=0);
        /**
        * Destructor
        */
        virtual ~COrthographicCameraEditorFactory() {};
        /** @copydoc CBaseEditorFactory::duplicate(OgitorsView *view) */
        virtual CBaseEditorFactory* duplicate(OgitorsView *view) {};
        /** @copydoc CBaseEditorFactor::CreateObject(CBaseEditor **, Ogre::NameValuePairList &) */
        virtual CBaseEditor *CreateObject(CBaseEditor **parent, OgitorsPropertyValueMap &params);
        /** @copydoc CBaseEditorFactor::GetPlaceHolderName) */
        virtual Ogre::String GetPlaceHolderName() {return "";};
// 

    };

} 
