using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class EndTrigger : MonoBehaviour {
    private GameObject m_deadPrefab;
    // Use this for initialization
    void Start () {
        m_deadPrefab = Resources.Load<GameObject>("prefab/DeadEvent");
    }
	
	// Update is called once per frame
	void Update () {
		
	}
    private void OnTriggerEnter2D(Collider2D collision)
    {
        //GameObject obj =  GameObject.Find("StartPoint");
        //GameObject player = GameObject.FindGameObjectWithTag("Player");
        Instantiate<GameObject>(m_deadPrefab);
        //SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);

    }
}
