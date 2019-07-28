using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class CPinchZoom : MonoBehaviour {

    public float perspectiveZoomSpeed = 0.5f;
    public float orthoZoomSpeed = 0.5f;
    public Text test;

    Camera mainCamera;

    void Awake()
    {
         mainCamera = Camera.main;
    }

    void Update()
    {
        if(Input.touchCount == 2)
        {
            Touch touchZero = Input.GetTouch(0);
            Touch touchOne = Input.GetTouch(1);

            Vector2 touchZeroPrevPos = touchZero.position - touchZero.deltaPosition;
            Vector2 touchOnePrevPos = touchOne.position - touchOne.deltaPosition;

            float prevTouchDeltaMsg = (touchZeroPrevPos - touchOnePrevPos).magnitude;
            float touchDeltaMsg = (touchZero.position - touchOne.position).magnitude;

            float deltaMagnitudediff = prevTouchDeltaMsg - touchDeltaMsg;

            if (mainCamera.orthographic)
            {
                mainCamera.orthographicSize += deltaMagnitudediff * orthoZoomSpeed;

                mainCamera.orthographicSize = Mathf.Max(mainCamera.orthographicSize, 0.1f);
                test.text = "or어쩌구저쩌구";
            }
            else
            {
                float zoom = transform.position.y + (deltaMagnitudediff * perspectiveZoomSpeed);

                transform.position = new Vector3(transform.position.x, Mathf.Clamp(zoom,5f,30f) ,transform.position.z);
                
                test.text = zoom.ToString();
            }
        }
    }
	
}
