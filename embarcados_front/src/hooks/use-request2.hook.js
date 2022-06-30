import { useState, useCallback } from 'react';
import axios from 'axios';

export const useRequest = ({ method, baseURL, route }) => {
  const [data, setData] = useState(null);
  const [errorCode, setErrorCode] = useState(null);
  const [loading, setLoading] = useState(false);

  const request = useCallback(
    async ({ params, bodyData, withCredentials, onSuccess }) => {
      try {
        setLoading(true);
        console.log('request', baseURL, route);
        const response = await axios.request({
          method: method || 'get',
          baseURL: baseURL || 'https://project-rfid-embarcados.herokuapp.com/',
          url: route,
          params,
          data: bodyData,
          withCredentials: withCredentials || false,
        });

        console.log(bodyData)
        setData(response.data);
        onSuccess(response.data);
      } catch (err) {
        if (err.isAxiosError) {
          const error = err;

          setErrorCode(String(error?.response?.status));
        }
      } finally {
        setLoading(false);
      }
    },
    [route],
  );

  return { request, data, loading, errorCode };
};